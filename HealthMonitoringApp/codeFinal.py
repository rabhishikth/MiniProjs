# -*- coding: utf-8 -*-
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC
from sklearn.metrics import confusion_matrix, classification_report
from sklearn.preprocessing import StandardScaler
import joblib
import gradio as gr

# Load and preprocess data
def load_and_preprocess_data():
    # Load dataset
    try:
        df = pd.read_csv('qt_dataset.csv', encoding='latin1')
    except FileNotFoundError:
        raise FileNotFoundError("Dataset file 'qt_dataset.csv' not found. Please download it from Kaggle and place in the same directory.")
    
    # Show class distribution
    print("\nOriginal Class Distribution:")
    print(df['Result'].value_counts())
    
    # Preprocessing
    df.set_index('ID', inplace=True)
    df['Result'].replace(['Positive', 'Negative'], [1, 0], inplace=True)
    
    # Split data
    x = df.drop('Result', axis=1)
    y = df['Result']
    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.3, random_state=42)
    
    return x_train, x_test, y_train, y_test

# Train and save model
def train_model(x_train, y_train):
    # Clean data
    y_train_cleaned = y_train.dropna()
    x_train_cleaned = x_train.loc[y_train_cleaned.index]
    
    # Show training class distribution
    print("\nTraining Class Distribution:")
    print(y_train_cleaned.value_counts())
    
    # Scale data
    scaler = StandardScaler()
    x_train_scaled = scaler.fit_transform(x_train_cleaned)
    
    # Train model with balanced class weights
    model = SVC(kernel='rbf', class_weight='balanced', probability=True)
    model.fit(x_train_scaled, y_train_cleaned)
    
    # Evaluate on training data
    train_pred = model.predict(x_train_scaled)
    print("\nTraining Performance:")
    print(classification_report(y_train_cleaned, train_pred))
    
    # Save model and scaler
    joblib.dump(model, 'model.pkl')
    joblib.dump(scaler, 'scaler.pkl')
    
    return model, scaler

# Evaluate model on test set
def evaluate_model(x_test, y_test):
    try:
        model = joblib.load('model.pkl')
        scaler = joblib.load('scaler.pkl')
    except FileNotFoundError:
        print("Model files not found. Please train the model first.")
        return
    
    # Clean test data
    y_test_cleaned = y_test.dropna()
    x_test_cleaned = x_test.loc[y_test_cleaned.index]
    x_test_scaled = scaler.transform(x_test_cleaned)
    
    # Evaluate
    test_pred = model.predict(x_test_scaled)
    print("\nTest Performance:")
    print(classification_report(y_test_cleaned, test_pred))
    
    # Confusion matrix
    cm = confusion_matrix(y_test_cleaned, test_pred)
    plt.figure(figsize=(8, 6))
    sns.heatmap(cm, annot=True, fmt="d", cmap="Blues",
                xticklabels=['Negative', 'Positive'],
                yticklabels=['Negative', 'Positive'])
    plt.title('Confusion Matrix')
    plt.xlabel('Predicted')
    plt.ylabel('Actual')
    plt.savefig('confusion_matrix.png')
    plt.close()
    print("Confusion matrix saved as 'confusion_matrix.png'")

# Prediction function
def predict(oxygen, pulse_rate, temperature):
    try:
        model = joblib.load('model.pkl')
        scaler = joblib.load('scaler.pkl')
        
        # Validate inputs
        if None in [oxygen, pulse_rate, temperature]:
            return "❌ Please enter all values"
        
        # Check reasonable ranges
        if not (70 <= oxygen <= 100):
            return f"❌ Oxygen level {oxygen}% is outside normal range (70-100%)"
        if not (40 <= pulse_rate <= 120):
            return f"❌ Pulse rate {pulse_rate}bpm is outside normal range (40-120bpm)"
        if not (35 <= temperature <= 42):
            return f"❌ Temperature {temperature}°C is outside normal range (35-42°C)"
            
        # Prepare input
        inputs = np.array([oxygen, pulse_rate, temperature]).reshape(1, -1)
        scaled_inputs = scaler.transform(inputs)
        
        # Get prediction and probabilities
        prediction = model.predict(scaled_inputs)
        probabilities = model.predict_proba(scaled_inputs)
        
        # Format output
        result = "Positive" if prediction[0] == 1 else "Negative"
        confidence = probabilities[0][1] if prediction[0] == 1 else probabilities[0][0]
        
        # Interpretation
        interpretation = ""
        if result == "Positive":
            if oxygen < 92:
                interpretation += "⚠️ Low oxygen level detected\n"
            if pulse_rate > 100:
                interpretation += "⚠️ Elevated pulse rate detected\n"
            if temperature > 37.5:
                interpretation += "⚠️ Elevated temperature detected\n"
        
        return (f"🔍 Prediction: {result}\n"
                f"🔼 Confidence: {confidence:.1%}\n\n"
                f"📊 Vital Signs:\n"
                f"• Oxygen: {oxygen}% {'(Normal)' if oxygen >= 95 else '(Low)'}\n"
                f"• Pulse: {pulse_rate}bpm {'(Normal)' if 60 <= pulse_rate <= 100 else '(Abnormal)'}\n"
                f"• Temp: {temperature}°C {'(Normal)' if 36 <= temperature <= 37.5 else '(Abnormal)'}\n\n"
                f"{interpretation}")
    
    except Exception as e:
        return f"❌ Error: {str(e)}"

# Main function
def main():
    print("===Health Monitoring System ===")
    
    try:
        # Load and preprocess data
        x_train, x_test, y_train, y_test = load_and_preprocess_data()
        
        # Train model (comment out after first run to use saved model)
        print("\nTraining model...")
        train_model(x_train, y_train)
        
        # Evaluate model
        print("\nEvaluating model...")
        evaluate_model(x_test, y_test)
        
    except Exception as e:
        print(f"Error during setup: {str(e)}")
        print("Trying to load existing model...")
    
    # Create Gradio interface
    print("\nLaunching Gradio interface...")
    iface = gr.Interface(
        fn=predict,
        inputs=[
            gr.Slider(70, 100, value=98.0, label="Oxygen Saturation (%)", 
                     info="Normal range: 95-100%"),
            gr.Slider(40, 120, value=72, label="Pulse Rate (bpm)", 
                     info="Normal range: 60-100bpm"),
            gr.Slider(35, 42, value=36.8, label="Temperature (°C)", 
                     info="Normal range: 36-37.5°C")
        ],
        outputs=gr.Textbox(label="Health Assessment"),
        examples=[
            [98.0, 72, 36.8],  # Healthy
            [91.0, 105, 38.2],  # Potentially problematic
            [88.0, 115, 39.0]   # Critical
        ],
        title="🏥 Hospital Health Monitoring System",
        description="Enter patient vitals to assess health status (Positive/Negative)",
        theme="soft",
        allow_flagging="never"
    )
    
    iface.launch()

if __name__ == "__main__":
    main()