#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_sendTimeout();
    void appendLog(const QString &msg);

private:
    Ui::MainWindow *ui;

    QUdpSocket *m_socket;
    QTimer *m_timer;

    int m_initialSize;
    int m_curSize;
    int m_maxSize;
    bool m_incSize;
    bool m_incContent;
    quint64 m_contentBase64;
    quint8 m_patternByte;
    QString m_destIp;
    quint16 m_destPort;

    void updateUiForRunning(bool running);
    QByteArray makePayload();
};
#endif // MAINWINDOW_H
