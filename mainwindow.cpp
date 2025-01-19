#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "head/materiel.h"
#include "head/amortissement_lineaire.h"
#include <QMessageBox>
#include "head/amortissement_degressif.h"
#include <QFileDialog>
#include <QTextStream>
#include <QTableWidget>
#include <QHeaderView>
#include <QFile>


using namespace std ;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("calcultor app");
    QIcon wicon(":/files/profits_32.png");
    if (wicon.isNull()) {
        qDebug() << "no icon winicon";
    } else {
        qDebug() << "there is an icon";
    }
    setWindowIcon(wicon);
    set_invisible_inputs_amort(false);

    QPixmap time(":/files/time.png");
    if (time.isNull()) {
        qDebug() << "time icone non trouvé" ;
    };
    QPixmap stats(":/files/bar-chart.png");
    QPixmap material(":/files/processing.png");
    QPixmap calendar(":/files/calendar.png");
    QIcon back(":/files/back-button.png");
    QIcon download(":/files/downloads.png");
    QPixmap title(":/files/stat__.png");
    QIcon next(":/files/right.png");

    ui->download->setIcon(download);
    ui->download->setCursor(Qt::PointingHandCursor);
    ui->navigation->setIcon(next);
    ui->titleIcon->setPixmap(title);
    ui->back->setIcon(back);
    ui->timeIcon->setPixmap(time);
    ui->statIcon->setPixmap(stats);
    ui->materialIcon->setPixmap(material);
    ui->calendarIcon->setPixmap(calendar);

    QDateEdit *dateEdit = ui->date_selection;
    dateEdit->setDate(QDate::currentDate());
    ui->date_selection->setDisplayFormat("dd/MM/yyyy");


    set_materiel_items();

    ui->prix->setPlaceholderText("prix en MAD");

    ui->table_amortissement->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->table_amortissement->clearSelection() ;

      ui->table_amortissement->setMaximumHeight(400);

    ui->table_amortissement->setStyleSheet(
        "QTableWidget {"

        "   border: 1px solid #dcdcdc;;"
        "   gridline-color: transparent;"
         "background: white;"

        "}"
        "QTableWidget::item {"
        "   border: none;"
        "border-bottom: 1px solid #dcdcdc;"
        "color:black;"
        "}"
       "QTableWidget::item:selected {"
        "   background-color: #2F2F2F;"
        "   color: white;"
        "}"
        "QTableWidget::item:selected:focus {"
        "   background-color: #87CEFA;"

        "}"
         "QMessageBox{"
         "color:black;"
         "}"

         "QTableWidget::verticalScrollBar {"
    "    width: 5px;"  // Modifier l'épaisseur de la scrollbar verticale
    "    background-color: #f0f0f0;"  // Couleur de fond de la scrollbar
    "    border: 1px solid #888;"  // Bordure de la scrollbar
    "}"
    "QTableWidget::verticalScrollBar::handle {"
    "    background-color: #a0a0a0;"  // Couleur de la barre de défilement
    "    border-radius: 7px;"  // Bordure arrondie de la barre
    "}"
        );

}

MainWindow::~MainWindow()
{
    delete ui;
}


void msg_err(QString message) {
    QMessageBox msg ;
     msg.setIcon(QMessageBox::Warning);
    msg.setText("<font color='black'>" + message + "</font>") ;
     msg.setStyleSheet("QMessageBox { background-color: white; color: black;font-size: small; }");
    msg.addButton(QMessageBox::Ok)->setStyleSheet("background : white ; color : black");
    msg.exec() ;
}

void msg_success(QString message) {
    QMessageBox msg ;
    msg.setIcon(QMessageBox::Information);
    msg.setText("<font color='black'>" + message + "</font>") ;
    msg.setStyleSheet("QMessageBox { background-color: white; color: black;font-size: small; }");
    msg.addButton(QMessageBox::Ok)->setStyleSheet("background : white ; color : black");
    msg.exec() ;
}

void MainWindow::create_linear(materiel m, float prix, float taux_afficher)
{
    QVector<amortissement_lineaire> amortissements = amortissement_lineaire::calculate(m, prix);


    ui->taux_amortissement->setText(QString::number(taux_afficher, 'f', 2) + " %");
    ui->table_amortissement->setColumnCount(4);

    ui->table_amortissement->setRowCount(amortissements.size() + 1);
    ui->table_amortissement->setItem(0, 0, new QTableWidgetItem("année"));
    ui->table_amortissement->setItem(0, 1, new QTableWidgetItem("dotation annuelle"));
    ui->table_amortissement->setItem(0, 2, new QTableWidgetItem("cumule dotation"));
    ui->table_amortissement->setItem(0, 3, new QTableWidgetItem("veleur net (MAD)"));

    int rowHeight = ui->table_amortissement->rowHeight(0);
    int rowCount = ui->table_amortissement->rowCount();
    int tableHeight = rowHeight * rowCount;
    ui->table_amortissement->setFixedHeight(tableHeight);
    for (int i = 0; i < amortissements.size(); i++) {
        amortissement_lineaire &a = amortissements[i];

        ui->table_amortissement->setItem(i + 1,
                                         0,
                                         new QTableWidgetItem(QString::number(a.get_annee())));
        ui->table_amortissement
            ->setItem(i + 1, 1, new QTableWidgetItem(QString::number(a.get_base(), 'f', 2)));
        ui->table_amortissement
            ->setItem(i + 1, 2, new QTableWidgetItem(QString::number(a.get_cumule(), 'f', 2)));
        ui->table_amortissement->setItem(i + 1,
                                         3,
                                         new QTableWidgetItem(QString::number(a.get_net(), 'f', 2)));
    }
}

void MainWindow::create_degressif(materiel m, float prix)
{
    if (m.get_dure_vie() < 3) {
        msg_err("une durée de vie inferieur à 3 ans ne presente pas d'amortissement degressif");
        return;
    }
    QVector<amortissement_degressif> amortissements = amortissement_degressif::calculate(m , prix) ;
     ui->taux_amortissement->setText(QString::number(amortissements[1].get_taux_degressif() , 'f' , 2)+" %");
    ui->table_amortissement->setColumnCount(7) ;
     ui->table_amortissement->setMaximumHeight(200);
    ui->table_amortissement->setRowCount(amortissements.size() + 1) ;
    ui->table_amortissement->setItem(0, 0, new QTableWidgetItem("annee"));
    ui->table_amortissement->setItem(0, 1, new QTableWidgetItem("base amortie(MAD)"));
    ui->table_amortissement->setItem(0, 2, new QTableWidgetItem("taux lineaire(%)"));
    ui->table_amortissement->setItem(0, 3, new QTableWidgetItem("taux degressif(%)"));
    ui->table_amortissement->setItem(0, 4, new QTableWidgetItem("dotation"));
     ui->table_amortissement->setItem(0, 5, new QTableWidgetItem("cumule dotation"));
      ui->table_amortissement->setItem(0, 6, new QTableWidgetItem("valeur net(MAD)"));

    int rowHeight = ui->table_amortissement->rowHeight(0);
    int rowCount = ui->table_amortissement->rowCount();
    int tableHeight = rowHeight * rowCount;

    ui->table_amortissement->setFixedHeight(tableHeight);
    for (int i = 0 ; i < amortissements.size() ; i++) {
        amortissement_degressif& a = amortissements[i];

        ui->table_amortissement->setItem(i + 1, 0, new QTableWidgetItem(QString::number(a.get_annee())));
        ui->table_amortissement->setItem(i + 1, 1, new QTableWidgetItem(QString::number(a.get_base_amortie(), 'f', 2)));
        ui->table_amortissement->setItem(i + 1, 2, new QTableWidgetItem(QString::number(a.get_taux_lineaire(), 'f', 2)));
        ui->table_amortissement->setItem(i + 1, 3, new QTableWidgetItem(QString::number(a.get_taux_degressif(), 'f', 2)));
        ui->table_amortissement->setItem(i + 1, 4, new QTableWidgetItem(QString::number(a.get_dotation(), 'f', 2)));
        ui->table_amortissement->setItem(i + 1, 5, new QTableWidgetItem(QString::number(a.get_cumule(), 'f', 2)));
        ui->table_amortissement->setItem(i + 1, 6, new QTableWidgetItem(QString::number(a.get_valeur_net(), 'f', 2)));

    }
}

void MainWindow::on_calculer_clicked()
{
    int id = ui->materiel_selection->currentData().toInt() ;
    materiel mat = materiel::get_by_id(id) ;
    mat.set_date(ui -> date_selection ->date()) ;
    ui->date_aquisition->setText(mat.get_date().toString("dd/MM/yyyy"));
    ui->materiel->setText(mat.get_nom());
    float taux_afficher = mat.get_taux();
    ui->duree->setText(QString::number(mat.get_dure_vie())+" ans") ;
    int prix = ui->prix ->text().toInt() ;
    if (prix <= 0) {
        msg_err("le prix doit etre une nombre strictement positif") ;
        return;
    }

    QString choix = ui->amort_selection->currentText();
    choix == "linéaire" ? create_linear(mat, prix , taux_afficher) : create_degressif(mat , prix);
}


void MainWindow::on_download_clicked()
{
    QString tempFileName = QDir::temp().filePath(
        "amortissement.csv");
    QFile file(tempFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Impossible d'ouvrir le fichier temporaire pour écriture";
        return;
    }

    QTextStream out(&file);

    if (ui->table_amortissement->rowCount() == 0) {
        msg_err("veuiller effectuer des calculs");
        return;
    }

    for (int row = 0; row < ui->table_amortissement->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < ui->table_amortissement->columnCount(); ++col) {
            QTableWidgetItem *item = ui->table_amortissement->item(row, col);
            if (item) {
                rowData << item->text();
            } else {
                rowData << "";
            }
        }
        out << rowData.join(",") << "\n";
    }


    file.close();
    QString saveFileName = QFileDialog::getSaveFileName(this,
                                                        "Enregistrer le fichier CSV",
                                                        "",
                                                        "Fichiers CSV (*.csv)");
    if (saveFileName.isEmpty()) {
        qDebug() << "Aucun fichier sélectionné, opération annulée.";
        return;
    }


    if (!saveFileName.endsWith(".csv", Qt::CaseInsensitive)) {
        saveFileName.append(".csv");
    }

    if (QFile::copy(tempFileName, saveFileName)) {
        msg_success("le fichier a ete telecharger dans "+saveFileName);
    } else {
        qWarning() << "Erreur lors du déplacement du fichier CSV.";
    }

    QFile::remove(tempFileName);
}

void MainWindow::on_navigation_clicked()
{
    change_title("liste des materiaux",
                 ":/files/list.png",
                 "total");
    set_invisible_inputs(false);
    set_invisible_inputs_amort(true);
    set_materiel_table();
    QPixmap icon(":/files/sigma.png");
    ui->calendarIcon->setPixmap(icon);
}

void MainWindow::change_title(QString text, QString path , QString date_label)
{
    ui->location->setText(text);
    QPixmap title(path);
    ui->titleIcon->setPixmap(title);
    ui->date_label->setText(date_label);
}

void MainWindow::on_ajout_clicked()
{
    QString nom = ui->nom_materiel->text();
    int vie = ui->duree_vie_materiel->text().toInt();
    if (nom == "" || vie < 0) {
        msg_err("veuiller remplir tous les champs | la duree de vie doit être superieure 0") ;
        return;
    }

    optional<materiel> existance = materiel::check_doublon(nom);
    if (existance) {
        update_action(existance->get_nom(), vie);
    } else {
        insert_action(nom, vie);
    }


}

void MainWindow::set_invisible_inputs(bool state)
{
    ui->amort_selection->setVisible(state);
    ui->date_selection->setVisible(state);
    ui->prix->setVisible(state);
    ui->materiel_selection->setVisible(state);
    ui->calculer->setVisible(state);
}

void MainWindow::set_invisible_inputs_amort(bool state)
{
    ui->nom_materiel->setVisible(state);
    ui->duree_vie_materiel->setVisible(state);
    ui->nom_materiel->setPlaceholderText("nom du materiel");
    ui->duree_vie_materiel->setPlaceholderText("duree de vie (année)");
    ui->ajout->setVisible(state);
}

void MainWindow::on_back_clicked()
{
    set_invisible_inputs(true);
    set_invisible_inputs_amort(false);
    ui->table_amortissement->clearContents();
    change_title("amortissement calculator",
                 ":/files/stat__.png",
                 "date");
    QPixmap icon(":/files/calendar.png");
    ui->calendarIcon->setPixmap(icon);
}

void MainWindow::set_materiel_table(){
    QVector<materiel> materiels = materiel::get_all();
    ui->table_amortissement->setColumnCount(2);
    ui->table_amortissement->setMaximumHeight(400);
    ui->table_amortissement->setRowCount(materiels.size() + 1);
    ui->date_aquisition->setText(QString::number(materiels.size()));
    int rowHeight = ui->table_amortissement->rowHeight(0);
    int rowCount = ui->table_amortissement->rowCount();
    int tableHeight = rowHeight * rowCount;
    ui->table_amortissement->setFixedHeight(tableHeight);
    ui->table_amortissement->setItem(0, 0, new QTableWidgetItem("materiel"));
    ui->table_amortissement->setItem(0, 1, new QTableWidgetItem("duree de vie"));

    for (int i = 0; i < materiels.size(); i++) {
        materiel &m = materiels[i];
        ui->table_amortissement-> setItem(i+1, 0, new QTableWidgetItem(m.get_nom()));
        ui->table_amortissement-> setItem(i+1, 1, new QTableWidgetItem(QString::number(m.get_dure_vie())));

    }
}

bool MainWindow::msg_choix(QString nom)
{
    QMessageBox messageBox;
    messageBox.setWindowTitle("Confirmation");
    messageBox.setText("<font color : black ;>" +nom +" existe deja dans la base donneée voulez mettre a jour?" + "</font>");
    messageBox.setStyleSheet("QMessageBox { background-color: white;  }");
    messageBox.setIcon(QMessageBox::Question);
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);

    int ret = messageBox.exec();
    bool choice;
    choice = QMessageBox::Yes;
    return choice;
}

void MainWindow::update_action(QString nom, int vie)
{
    if (!msg_choix(nom)) {
        return;
    } else {
        materiel::update_materiel(nom, vie);
        update_row_materiel(nom, vie);
        set_materiel_items();
    }
}

void MainWindow::insert_action(QString nom , int vie){
    materiel::insert(nom, vie);
    materiel get_nom = materiel::get_by_name(nom);
    ui->table_amortissement->insertRow(1);
    ui->table_amortissement->setItem(1, 0, new QTableWidgetItem(get_nom.get_nom()));
    ui->table_amortissement->setItem(1, 1, new QTableWidgetItem(QString::number(get_nom.get_dure_vie())));
    ui->materiel_selection->addItem(get_nom.get_nom() , get_nom.get_id());
    int total = ui->date_aquisition->text().toInt() + 1;
    ui->date_aquisition->setText(QString::number(total));
}

void MainWindow::set_materiel_items()
{
    ui->materiel_selection->clear();
    QVector<materiel> materiels = materiel::get_all();
    for (materiel &mat : materiels) {
        ui->materiel_selection->addItem(mat.get_nom(), mat.get_id());
    }
}

void MainWindow::update_row_materiel(QString nom, int vie)
{
    QTableWidget *tab = ui->table_amortissement;
    for (int row = 1; row < tab->rowCount(); row++) {
        QTableWidgetItem *col1 = tab->item(row, 0);
        if (col1->text() == nom) {
            QTableWidgetItem *modify = tab->item(row, 1);
            modify->setText(QString::number(vie));
        }
    }
}

