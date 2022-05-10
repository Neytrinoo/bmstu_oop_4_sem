#include <QDoubleValidator>
#include <QFileDialog>
#include <iostream>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "request.h"
#include "transforms.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QGraphicsScene *canvas = new QGraphicsScene(this);
    ui->graphicsView->setScene(canvas);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    canvas->setSceneRect(ui->graphicsView->geometry());
}

MainWindow::~MainWindow()  {
    Request quit;

    doRequest(quit, actions::QUIT);

    delete ui;
    delete double_validator_;
}


void MainWindow::on_load_file_btn_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, "", "", tr("Images (*.txt)"));
    ui->input_filepath->setText(filename);

    Request load_shape_request;

    load_shape_request.filename_ = filename.toStdString().c_str();

    Canvas canv;
    canv.scene = ui->graphicsView->scene();
    load_shape_request.canvas_ = canv;

    errorCode result = doRequest(load_shape_request, actions::LOAD_FIGURE);
    if (result == errorCode::SUCCESS) {
        result = doRequest(load_shape_request, actions::DRAW_FIGURE);
    }

    if (result != errorCode::SUCCESS) {
        showErrorMessage(result);
    }
}


void MainWindow::on_do_transfer_btn_clicked() {
    TransferSettings ts = initTransferSettings(ui->transfer_dx->value(), ui->transfer_dy->value(), ui->transfer_dz->value());
    Request transfer_shape_request;
    transfer_shape_request.canvas_ = Canvas {ui->graphicsView->scene()};
    transfer_shape_request.transformAction_.ts = ts;

    errorCode result = doRequest(transfer_shape_request, actions::TRANSFER_FIGURE);
    if (result != errorCode::SUCCESS) {
        showErrorMessage(result);
    } else {
        result = doRequest(transfer_shape_request, actions::DRAW_FIGURE);
        if (result != errorCode::SUCCESS) {
            showErrorMessage(result);
        }
    }
}


void MainWindow::on_do_turn_btn_clicked() {
    RotateSettings rs = initRotateSettings(ui->turn_ax->value(), ui->turn_ay->value(), ui->turn_az->value());
    Request rotate_shape_request;
    rotate_shape_request.canvas_ = Canvas {ui->graphicsView->scene()};
    rotate_shape_request.transformAction_.rs = rs;

    errorCode result = doRequest(rotate_shape_request, actions::SET_ROTATE_CENTER_IN_SHAPE_CENTER);
    if (result != errorCode::SUCCESS) {
        showErrorMessage(result);
    } else {
        result = doRequest(rotate_shape_request, actions::ROTATE_FIGURE);
        if (result != errorCode::SUCCESS) {
            showErrorMessage(result);
        } else {
            result = doRequest(rotate_shape_request, actions::DRAW_FIGURE);
            if (result != errorCode::SUCCESS) {
                showErrorMessage(result);
            }
        }
    }
}


void MainWindow::on_do_scale_btn_clicked() {
    ScaleSettings ss = initScaleSettings(ui->scale_dx->value(), ui->scale_dy->value(), ui->scale_dz->value());
    Request scale_shape_request;
    scale_shape_request.canvas_ = Canvas {ui->graphicsView->scene()};
    scale_shape_request.transformAction_.ss = ss;

    errorCode result = doRequest(scale_shape_request, actions::SET_SCALE_CENTER_IN_SHAPE_CENTER);

    if (result != errorCode::SUCCESS) {
        showErrorMessage(result);
    } else {
        result = doRequest(scale_shape_request, actions::SCALE_FIGURE);
        if (result != errorCode::SUCCESS) {
            showErrorMessage(result);
        } else {
            result = doRequest(scale_shape_request, actions::DRAW_FIGURE);
            if (result != errorCode::SUCCESS) {
                showErrorMessage(result);
            }
        }
    }
}


void MainWindow::on_save_as_btn_clicked()
{
    Request save_shape;
    save_shape.filename_ = "output.txt";

    errorCode result = doRequest(save_shape, actions::SAVE_FIGURE_AT_FILE);
    if (result != errorCode::SUCCESS) {
        showErrorMessage(result);
    }
}

