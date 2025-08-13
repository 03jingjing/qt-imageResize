#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressDialog>
#include <QLineEdit>
#include <QVector>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    //结构体管理
    struct RoiConfig{
        QLineEdit* lineEdit;
        QString outputDirName;
        bool enabled;
    };
    QVector<RoiConfig> roiConfigs;
    void initializeRoiConfigs();

    // 处理所有图片
    void processImages();

    // 处理单张图片
    bool processSingleRoi(const QString &inputPath, const QString &outputDir, QLineEdit* roiLineEdit);

    // 解析ROI参数
    bool parseRoiParameters(QLineEdit* roiLineEdit,int &x, int &y, int &width, int &height);
    // 解析Resize参数
    bool processResize(const QString &inputPath, const QString &outputDir);

};
#endif // MAINWINDOW_H
