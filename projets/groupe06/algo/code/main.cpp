#include "mainwindow.h"
#include <QSplashScreen>
#include <QPixmap>
#include <QTimer>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QPixmap pixmap(":/images/splash.png");  // ton image splash
    QSplashScreen splash(pixmap);
    splash.show();

    // Pause de 2 secondes (ou plus) pendant que l’animation est visible
    QTimer::singleShot(2000, &splash, &QSplashScreen::close);

    MainWindow w;
    QTimer::singleShot(2000, &w, &QWidget::show); // Affiche la fenêtre principale après le splash

    return app.exec();
}
