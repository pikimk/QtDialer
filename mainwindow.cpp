#include "mainwindow.h"
#include "countrycode.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QMap>
#include <QTableView>
#include <QHeaderView>



#define ICONPATH ":/icons/resources/resources/countries/flags/"
#define FILEPATH ":/resources/resources/countries/countries.txt"



QMap<int,CountryCode> parseFile(QString filePath);
QMap<int,CountryCode> map = parseFile(FILEPATH);
QStandardItemModel *model;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

  model = new QStandardItemModel(0,3,this);


  for(QMap<int,CountryCode>::Iterator it = map.begin();it!=map.end();it++){

      QStandardItem *iconItem = new QStandardItem();
      iconItem->setIcon(QIcon(it.value().getIconFullPath(ICONPATH)));
      QStandardItem *stateName = new QStandardItem(it.value().getCountryName());
      QStandardItem *prefix = new QStandardItem(QString("+" + QString::number(it.key())));
      prefix->setTextAlignment(Qt::AlignRight);


      QList<QStandardItem*> itemList {
          iconItem,
          stateName,
          prefix
      };

      model->appendRow(itemList);

    }

  QTableView *tableView = new QTableView(this);
        tableView->setModel( model );
        tableView->verticalHeader()->hide();
        tableView->horizontalHeader()->hide();
        tableView->resizeColumnsToContents();
        tableView->setGridStyle(Qt::NoPen);
        tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setAutoScroll(false);

    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox->setView(tableView);
    ui->comboBox->setModel(model);
    ui->comboBox->setCurrentIndex(-1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


QMap<int,CountryCode> parseFile(QString filePath){

    QMap<int,CountryCode> countryMap;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){

        QMessageBox  msgFileNotOpened(QMessageBox::Critical,"Error","Error opening file!");
        msgFileNotOpened.exec();

    }else{

        QTextStream stream(&file);
        while(! stream.atEnd()){
           QString line = stream.readLine();
           QStringList list = line.split(QLatin1Char(','));
           QString icon = list.at(0);
           int countryCode = list.at(1).toInt();
           QString countryName = list.at(2);
           QString countryShort = list.at(3);
           CountryCode countryObj(icon,countryName,countryShort,countryCode);
           map.insert(countryCode,countryObj);
        }

        file.close();
    }
    return countryMap;
}



void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString currentInput = arg1;
    currentInput.remove("+");

    int key = 0;
    for(int i = 4; i > 0; i-- ){
         key = currentInput.left(i).toInt();
        if(map.contains(key)) break;
    };

    if ( map.contains(key) ){
        CountryCode cc = map[key];
        QList lists = model->findItems("+"+QString::number(cc.getCountryPrefix()),Qt::MatchExactly,2);
        if(!lists.isEmpty()){
           QModelIndex index = lists.at(0)->index();        
           if (index.row() != ui->comboBox->currentIndex()){
                ui->comboBox->setCurrentIndex(index.row());
                QString keyString = QString::number(key);
                QString subtract = arg1.mid(keyString.size() + 1);
                ui->comboBox->activated(index.row());
                ui->comboBox->setCurrentText("+" + keyString + subtract);
           }
        };
    }
}



void MainWindow::on_comboBox_activated(int index)
{
   QStandardItem *item = model->item(index,2);
   ui->comboBox->setCurrentText(item->text());
}



void MainWindow::on_textEdit_textChanged()
{
    QString textGet = ui->textEdit->toPlainText();
    int textSize = textGet.size();
    int messageCount = (textSize / 160) + 1;
    int mod = textSize % 160;
    QString diference = QString::number(160-mod);
    QString messageCountStr = QString::number(messageCount);
    ui->label_2->setText(QString(diference + "/" + messageCountStr));
}

