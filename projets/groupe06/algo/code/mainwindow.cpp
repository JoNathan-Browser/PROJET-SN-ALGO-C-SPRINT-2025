#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QClipboard>
#include <QFontDialog> //pour setting
#include <QColorDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);//charge l'interface cree avec qt creator
    setWindowTitle("ICT-editor");
    ui->toolBar->setFloatable(false); //empêche qu’elle se détache dans une nouvelle fenêtre
    ui->toolBar->setMovable(false);//empêche qu’elle soit déplacée sur un autre bord
    this->setCentralWidget(ui->textEdit);//fais de la zone de texte la zonne central de l ápp
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    file_path="";//define a default file path for files storages
    ui->textEdit->setText(""); //reset the file text to do like you create a new file
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"open the file");
    QFile file(file_name);
    file_path=file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();

}


void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)) //Tente d’ouvrir le fichier en mode écriture (WriteOnly) et en mode texte (Text)
    {
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);//Crée un flux (out) pour écrire dans le fichier ouvert.
    QString text = ui->textEdit->toPlainText(); //recupere tout le texte dans la zone de texte
    out<<text; //ecrire tout le texte via le fichier
    file.flush();//vider le tampon
    file.close();//fermer le fichier

}


void MainWindow::on_actionSave_as_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"open the file");//Ouvre une boîte de dialogue pour demander à l'utilisateur où enregistrer le fichier.
    QFile file(file_name);//Crée un objet QFile pour gérer ce fichier
    file_path=file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out(&file);//Crée un flux QTextStream pour écrire dans le fichier.
    QString text = ui->textEdit->toPlainText();//QString text = ui->textEdit->toPlainText();
    out<<text;//Écrit le texte dans le fichier.
    file.flush();
    file.close();

}


void MainWindow::on_actionCut_triggered()
{
    // ui->textEdit->cut();
    //my own method
    //     #include <QClipboard>
    QString selectedText = ui->textEdit->textCursor().selectedText(); //recuperer le contenu de la zone de texte selectionnée
    if (!selectedText.isEmpty()) //controler si le texte selecctionné n'est pas vide avant d'agir
    {
        QClipboard *clipboard = QApplication::clipboard();//cree une variable pour acceder au presse papier pour l'utiliser #include <QClipboard>
        clipboard->setText(selectedText);//coller le texte recupere dasn le presspapier

        //le contenu si haut sert a copier le contenu pour implémenter la fonction cut il suffit
        //de faire en sorte que le code si haut supprime le contenu copié
        ui->textEdit->textCursor().removeSelectedText(); //supprimer le contenu selectionne avec la souris
    }
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
    //my own function
    //QClipboard *clipboard = QApplication::clipboard();
    //QString clipboad_text = clipboard->text(); //copier le texte du presse papier
    //ui->textEdit->insertPlainText(clipboad_text); // colle le texte à la position du curseur grace  a la fonction insertPlain...

}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionInfo_2_triggered()
{
    QString about_text;
    about_text="Authors: TSAFACK NGOUFACK Ernis Merkel, NOUBISSI MEIKEM Indira Leslie, NANA Laurianne Audrey, Tankam Soh Raoul Daril \nDate: 19/05/2025\n(c) Notepad (R)\n all rights reserved";
    QMessageBox::about(this,"informations",about_text); //about notpad is the title of the windows will appear
}


void MainWindow::on_actionPolice_triggered()
{
    // Choisir la police (y compris la taille)
    bool ok;
    QFont font = QFontDialog::getFont(&ok, ui->textEdit->font(), this, "Choisir la police");
    if (ok)
    {
        ui->textEdit->setFont(font);
    }

}




void MainWindow::on_actioncolor_triggered()
{
    // Choisir la couleur du texte
    QColor color = QColorDialog::getColor(Qt::black, this, "Choisir la couleur du texte");
    if (color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
}


