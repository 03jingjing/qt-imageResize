#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("图像批处理工具");
    // 初始化ROI配置结构体
    initializeRoiConfigs();
    for (RoiConfig& config : roiConfigs) {
        config.lineEdit->setPlaceholderText("ROI格式: x,y,width,height (例如: 100,100,200,200)");
    }    ui->ResizeROI->setPlaceholderText("缩放倍数: 大于0的数字 (例如: 0.5表示缩小一半)");
    ui->progressBar->setValue(0); // 初始值设为0
}

MainWindow::~MainWindow()
{
    delete ui;
}

//初始化五个roi结构体，类型是QLineEdit* lineEdit
void MainWindow::initializeRoiConfigs()
{
    roiConfigs = {
        {ui->ROI1, "roi1_result", false},
        {ui->ROI2, "roi2_result", false},
        {ui->ROI3, "roi3_result", false},
        {ui->ROI4, "roi4_result", false},
        {ui->ROI5, "roi5_result", false}
    };
}

//选择文件夹路径
void MainWindow::on_selectButton_clicked()
{
    QString inPath = QFileDialog::getExistingDirectory(this,
                                                       "选择图片文件夹",
                                                       QDir::homePath());
    if (!inPath.isEmpty()) {
        ui->INlineEdit->setText(inPath);
    }
}


// 统一解析ROI参数
bool MainWindow::parseRoiParameters(QLineEdit* roiLineEdit, int &x, int &y, int &width, int &height)
{
    QString roiText = roiLineEdit->text();
    QStringList parts = roiText.split(',');

    if (parts.size() != 4) {
        return false;
    }

    bool ok1, ok2, ok3, ok4;
    x = parts[0].toInt(&ok1);
    y = parts[1].toInt(&ok2);
    width = parts[2].toInt(&ok3);
    height = parts[3].toInt(&ok4);

    return ok1 && ok2 && ok3 && ok4;
}
//解析Resize参数
bool MainWindow::processResize(const QString &inputPath, const QString &outputDir)
{
    try {
        cv::Mat image = cv::imread(inputPath.toStdString());
        if (image.empty()) {
            qWarning() << "无法读取图像:" << inputPath;
            return false;
        }

        double scale = ui->ResizeROI->text().toDouble();
        cv::Mat processedImage;
        cv::resize(image, processedImage, cv::Size(), scale, scale, cv::INTER_AREA);

        QString outputPath = outputDir + "/" + QFileInfo(inputPath).fileName();
        if (!cv::imwrite(outputPath.toStdString(), processedImage)) {
            qWarning() << "无法保存图像:" << outputPath;
            return false;
        }

        return true;
    } catch (const std::exception &e) {
        qWarning() << "处理图像时出错:" << e.what();
        return false;
    }
}

bool MainWindow::processSingleRoi(const QString &inputPath, const QString &outputDir, QLineEdit* roiLineEdit)
{
    try {
        cv::Mat image = cv::imread(inputPath.toStdString());
        if (image.empty()) {
            qWarning() << "无法读取图像:" << inputPath;
            return false;
        }

        int x, y, width, height;
        if (!parseRoiParameters(roiLineEdit, x, y, width, height)) {
            return false;
        }

        // 确保ROI在图像范围内
        int maxX = std::min(x + width, image.cols);
        int maxY = std::min(y + height, image.rows);
        x = std::max(0, x);
        y = std::max(0, y);
        width = maxX - x;
        height = maxY - y;

        if (width <= 0 || height <= 0) {
            qWarning() << "ROI超出图像范围:" << inputPath;
            return false;
        }

        // 提取ROI
        cv::Rect roi(x, y, width, height);
        cv::Mat processedImage = image(roi).clone();

        // 保存处理后的图像
        QString outputPath = outputDir + "/" + QFileInfo(inputPath).fileName();
        if (!cv::imwrite(outputPath.toStdString(), processedImage)) {
            qWarning() << "无法保存图像:" << outputPath;
            return false;
        }

        return true;
    } catch (const std::exception &e) {
        qWarning() << "处理图像时出错:" << e.what();
        return false;
    }
}

void MainWindow::processImages()
{
    // 获取输入文件夹路径
    QString inputDir = ui->INlineEdit->text();
    if (inputDir.isEmpty() || !QDir(inputDir).exists()) {
        QMessageBox::warning(this, "错误", "请选择有效的图片文件夹");
        return;
    }

    // 检查并激活有效的ROI配置
    bool anyOperation = false;
    for (RoiConfig& config : roiConfigs) {
        int x, y, w, h;
        config.enabled = parseRoiParameters(config.lineEdit, x, y, w, h) && w > 0 && h > 0;
        anyOperation |= config.enabled;
    }
    // 检查缩放
    bool resizeEnabled = false;
    double scale = 0;
    if (!ui->ResizeROI->text().isEmpty()) {
        bool ok;
        scale = ui->ResizeROI->text().toDouble(&ok);
        resizeEnabled = ok && scale > 0;
        anyOperation |= resizeEnabled;
    }

    if (!anyOperation) {
        QMessageBox::warning(this, "警告", "没有设置有效的ROI或缩放参数");
        return;
    }

    // 创建输出目录
    QStringList outputDirs;
    for (RoiConfig& config : roiConfigs) {
        if (config.enabled) {
            QString outputDir = inputDir + "/" + config.outputDirName;
            QDir().mkpath(outputDir);
            outputDirs << outputDir;
        }
    }
    if (resizeEnabled) {
        QString outputDir = inputDir + "/resize_result";
        QDir().mkpath(outputDir);
        outputDirs << outputDir;
    }

    // 获取图片文件
    QDir dir(inputDir);
    QStringList imageFiles = dir.entryList({"*.jpg", "*.jpeg", "*.png", "*.bmp"}, QDir::Files);
    int totalFiles = imageFiles.size();

    if (totalFiles == 0) {
        QMessageBox::information(this, "提示", "文件夹中没有找到支持的图片文件");
        return;
    }

    // 初始化进度条
    ui->progressBar->setRange(0, totalFiles);
    int successCount = 0;
    int processedFiles = 0;

    // 处理每张图片
    for (const QString& fileName : imageFiles) {
        QString inputPath = inputDir + "/" + fileName;
        bool fileSuccess = true;

        // 处理所有激活的ROI
        for (int i = 0; i < roiConfigs.size(); i++) {
            if (roiConfigs[i].enabled) {
                if (!processSingleRoi(inputPath, outputDirs[i], roiConfigs[i].lineEdit)) {
                    fileSuccess = false;
                }
            }
        }

        // 处理缩放
        if (resizeEnabled) {
            if (!processResize(inputPath, outputDirs.last())) { // 缩放目录在最后
                fileSuccess = false;
            }
        }

        if (fileSuccess) successCount++;
        ui->progressBar->setValue(++processedFiles);
        QApplication::processEvents();
    }

    // 处理完成
    ui->progressBar->setValue(totalFiles);
    QMessageBox::information(this, "完成",
                             QString("处理完成：成功 %1/%2 张图片").arg(successCount).arg(totalFiles));
}

void MainWindow::on_pushButton_clicked()
{
    processImages();
}
