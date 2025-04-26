## Health Monitoring System

## 📌 Overview
A machine learning system that predicts patient health status (Positive/Negative) based on vital signs using SVM classification.

## to run for the first time:
pip install -r requirements.txt

and 

python hospital_management.py

## for subsequent runs 
python hospital_management.py --use-saved-model

📊 Performance Metrics
After first run, the system generates:

confusion_matrix.png - Model accuracy visualization

Training/test classification reports in console

⚠️ Troubleshooting
Issue	Solution
Dataset not found	Ensure qt_dataset.csv is in data/ folder
Model files missing	Run without --use-saved-model flag first
Port 7860 in use	Change port in Gradio launch parameters
Poor predictions	Check class balance in dataset

