#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostAddress>
#include <QDateTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_socket(new QUdpSocket(this)),
      m_timer(new QTimer(this)),
      m_initialSize(250),
      m_curSize(250),
      m_maxSize(250),
      m_incSize(false),
      m_incContent(false),
      m_contentBase64(0),
      m_patternByte(0x00),
      m_destIp("10.10.50.50"),
      m_destPort(5000)
{
    ui->setupUi(this);

    // set reasonable defaults in UI (if widgets exist)
    ui->ipLineEdit->setText(m_destIp);
    ui->portSpinBox->setValue(m_destPort);
    ui->sizeSpinBox->setValue(m_initialSize);
    ui->maxSizeSpinBox->setValue(m_maxSize);
    ui->intervalSpinBox->setValue(1000);
    ui->patternLineEdit->setText("0x00");
    ui->incSizeCheckBox->setChecked(false);
    ui->incContentCheckBox->setChecked(false);

    connect(m_timer, &QTimer::timeout, this, &MainWindow::on_sendTimeout);

    updateUiForRunning(false);
    appendLog("Ready.");
}

MainWindow::~MainWindow()
{
    m_timer->stop();
    delete ui;
}

void MainWindow::updateUiForRunning(bool running)
{
    ui->startButton->setEnabled(!running);
    ui->stopButton->setEnabled(running);

    // disable controls while running
    ui->ipLineEdit->setEnabled(!running);
    ui->portSpinBox->setEnabled(!running);
    ui->sizeSpinBox->setEnabled(!running);
    ui->maxSizeSpinBox->setEnabled(!running);
    ui->intervalSpinBox->setEnabled(!running);
    ui->patternLineEdit->setEnabled(!running);
    ui->incSizeCheckBox->setEnabled(!running);
    ui->incContentCheckBox->setEnabled(!running);
}

void MainWindow::appendLog(const QString &msg)
{
    QString time = QDateTime::currentDateTime().toString(Qt::ISODate);
    ui->logTextEdit->append(QString("[%1] %2").arg(time, msg));
}

void MainWindow::on_startButton_clicked()
{
    // read UI values
    m_destIp = ui->ipLineEdit->text().trimmed();
    m_destPort = static_cast<quint16>(ui->portSpinBox->value());
    m_initialSize = ui->sizeSpinBox->value();
    m_maxSize = ui->maxSizeSpinBox->value();
    if (m_maxSize < m_initialSize) m_maxSize = m_initialSize;
    int intervalMs = ui->intervalSpinBox->value();
    m_incSize = ui->incSizeCheckBox->isChecked();
    m_incContent = ui->incContentCheckBox->isChecked();

    // parse pattern hex like 0x41 or 41
    QString ptxt = ui->patternLineEdit->text().trimmed();
    bool ok = false;
    int patt = 0;
    if (ptxt.startsWith("0x", Qt::CaseInsensitive))
        patt = ptxt.mid(2).toInt(&ok, 16);
    else
        patt = ptxt.toInt(&ok, 16);
    if (!ok) patt = 0x00;
    m_patternByte = static_cast<quint8>(patt & 0xFF);

    // validate IP
    QHostAddress addr(m_destIp);
    if (addr.isNull()) {
        appendLog(QString("Invalid IP address: %1").arg(m_destIp));
        QMessageBox::warning(this, "Invalid IP", "Please enter a valid destination IP address.");
        return;
    }

    // initialize state
    m_curSize = m_initialSize;
    m_contentBase64 = 0;

    // start timer
    m_timer->start(intervalMs);
    updateUiForRunning(true);

    appendLog(QString("Started sender -> %1:%2 initial=%3 max=%4 interval=%5ms inc-size=%6 inc-content=%7 pattern=0x%8")
              .arg(m_destIp).arg(m_destPort).arg(m_initialSize).arg(m_maxSize)
              .arg(intervalMs).arg(m_incSize).arg(m_incContent)
              .arg(QString::number(m_patternByte,16).rightJustified(2,'0')));
}

void MainWindow::on_stopButton_clicked()
{
    m_timer->stop();
    updateUiForRunning(false);
    appendLog("Stopped.");
}
#if 0 // old which incremented last byte to 255 only
QByteArray MainWindow::makePayload()
{
    QByteArray payload;
    payload.resize(m_curSize);

    // Fill entire payload with the pattern byte
    payload.fill(static_cast<char>(m_patternByte));

    // If increment content is enabled, increment only the LAST BYTE
    if (m_incContent)
    {
        payload[m_curSize - 1] = static_cast<char>(m_contentBase);
        m_contentBase++;  // wraps automatically at 255 → 0
    }

    return payload;
}
}
#endif

//QByteArray MainWindow::makePayload()
//{
//    QByteArray payload;
//    payload.resize(m_curSize);

//    // Fill everything with the pattern byte
//    payload.fill(static_cast<char>(m_patternByte));

//    if (m_incContent)
//    {
//        // Write 32-bit counter into the LAST 4 bytes
//        quint32 counter = m_contentBase32;  // <-- we will add this new variable

//        payload[m_curSize - 4] = static_cast<char>((counter >> 24) & 0xFF);
//        payload[m_curSize - 3] = static_cast<char>((counter >> 16) & 0xFF);
//        payload[m_curSize - 2] = static_cast<char>((counter >> 8) & 0xFF);
//        payload[m_curSize - 1] = static_cast<char>((counter) & 0xFF);

//        m_contentBase32++;   // forward counting (no wrap until 4 billion+)
//    }

//    return payload;
//}
QByteArray MainWindow::makePayload()
{
    // Choose how many trailing bytes to use for the counter
    const int counterBytes = 4; // use 1,2,4,8 as you prefer
    if (m_curSize < counterBytes) {
        // fallback: no counter if payload too small
        QByteArray small;
        small.resize(m_curSize);
        small.fill(static_cast<char>(m_patternByte));
        return small;
    }

    QByteArray payload;
    payload.resize(m_curSize);
    payload.fill(static_cast<char>(m_patternByte));

    if (m_incContent)
    {
        // Use a 64-bit counter internally so it never wraps in practice
        // and write only the lower 'counterBytes' bytes to payload (big-endian)
        quint64 counter = m_contentBase64; // make sure this exists in header and initialized to 0
        for (int b = 0; b < counterBytes; ++b) {
            // index of the byte to write (big-endian at the end)
            int idx = m_curSize - counterBytes + b;
            int shift = 8 * (counterBytes - 1 - b);
            payload[idx] = static_cast<char>((counter >> shift) & 0xFF);
        }
        ++m_contentBase64;
    }

    return payload;
}




void MainWindow::on_sendTimeout()
{
    QByteArray payload = makePayload();

    qint64 sent = m_socket->writeDatagram(payload, QHostAddress(m_destIp), m_destPort);
    if (sent == -1) {
        appendLog(QString("Send failed: %1").arg(m_socket->errorString()));
    } else {
        // show bytes sent AND the payload data (hex, space-separated)
        appendLog(QString("Sent %1 bytes to %2:%3 | Data: %4")
                  .arg(sent)
                  .arg(m_destIp)
                  .arg(m_destPort)
                  .arg(QString(payload.toHex(' '))));
    }

    if (m_incSize) {
        m_curSize += 1;
        if (m_curSize > m_maxSize) {
            m_curSize = m_initialSize; // wrap
        }
    }
}
