#include "mainwindow.h"
#include "ui_mainwindow.h"


// to insert from file
    #include <QFileDialog>
    #include <QFile>
    #include <QTextStream>
    #include <QMessageBox>

#include <QString>
#include <QMap>
#include <QQueue>
// copy paste to check if num or n

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    using namespace std;
    QString text = ui->textEdit->toPlainText(); // read the input

    QMap<QString,QString> token;
    token["if"]     ="IF token";
    token["then"]   ="THEN token";
    token["end"]    ="END token";
    token["until"]  ="UNTIL token";
    token["write"]  ="WRITE token";
    token["else"]   ="ELSE token";
    token["repeat"] ="REPEAT token";
    token["read"]   ="READ token";

    enum state{start,inComment,inID,inNum,inAssign,done};
    state s=start;

    QString myCharContainer="";

    QVector <pair <QString,QString> > answer;

    QVector <QString>parserInput;
    QString type;
    for (int i = 0 ;i < (text.size()+1);i++){
        label:  switch (s) {   // the label to not waste the current char
                               // or u can use (i--) instead of (goto)
          case start:
                 myCharContainer="";
                 // comment
                 if (text[i]=='{')
                 {
                    s=inComment;
                 }
                 // assign
                 else if (text[i]==':') {
                    myCharContainer=myCharContainer+text[i];
                    s=inAssign;
                 }
                 // alphapitic
                 else if (text[i].isLetter())
                 {
                     myCharContainer=myCharContainer+text[i];
                     s=inID;
                 }
                 //  numbers
                 else if (text[i].isDigit())
                 {
                    myCharContainer=myCharContainer+text[i];
                    s=inNum;
                 }
                 else if (text[i]=='+') {
                     answer.push_back({"+","Plus"});
                     parserInput.push_back("PLUS");

                 }
                 else if (text[i]=='-') {
                     answer.push_back({"-","Minus"});
                     parserInput.push_back("MINUS");
                     //outputToken["-"]="MINUS";
                 }
                 else if (text[i]=='/') {
                    answer.push_back({"/","Divide"});
                    parserInput.push_back("DIVIDE");
                    // outputToken["/"]="DIVIDE";
                 }
                 else if (text[i]=='*') {
                    answer.push_back({"*","Multiple Operator"});
                    parserInput.push_back("MULTIPLE");
                    //outputToken["*"]="MULTIPLE";
                 }
                 else if (text[i]==';') {
                    answer.push_back({";","SemiColon"});
                    parserInput.push_back("SEMIColon");
                    //outputToken[";"]="SEMI";
                 }
                 else if ( text[i]== '.'){
                    answer.push_back({".","DOT"});
                    parserInput.push_back("DOT");
                 }
                 else if ( text[i]== '<'){
                    answer.push_back({"<","SmallerThan"});
                    parserInput.push_back("SmallerThan");
                 }
                 else if ( text[i]=='>')
                 {
                     answer.push_back({">","GreaterThan"});
                     parserInput.push_back("GreaterThan");
                 }
                 else if ( text[i]=='=')
                 {
                     answer.push_back({"=","equal"});
                     parserInput.push_back("Equal");
                 }
                break;


           case inAssign:
                   if (text[i]=='=')
                   {
                       myCharContainer= myCharContainer+(text[i]);
                        type="Assignment operator";

                   }
                   else{
                        i--;
                        type="Colon";
                   }
                   s=done;
                   goto label;
                          // or u can use (i--) instead of (goto)
                   break;
           case inComment:
                    while (text[i] !='}')
                        { i++;}
                    s=start;
                    break;
           case inNum:
                    while (text[i].isDigit())
                    {
                        myCharContainer=myCharContainer+text[i];
                        i++;
                    }
                    i--;
                    //outputToken[myCharContainer]="Number";
                    type="Number";
                    s=done;
                    //s=start;
                    goto label;
                     break;
           case inID:
                     while (text[i].isLetter()||text[i].isDigit())
                     {
                         myCharContainer=myCharContainer+text[i];
                         i++;
                     }
                     i--;
                     if (token.find(myCharContainer)!=token.end())
                     {
                         type=token[myCharContainer];
                     }
                     else type="identefier";
                     s=done;
                    goto label;
            break;

          case done:
                 //container.push_back(myCharContainer);
                 answer.push_back({myCharContainer,type});
                 parserInput.push_back(type);
                 s=start;
           break;
          }
      }

    // to not repeat the data
   // ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);

    for (QVector< pair <QString,QString> >::iterator it=answer.begin(); it != answer.end(); it++){
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        QTableWidgetItem *newItem1 = new QTableWidgetItem(it->first);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, newItem1);
        QTableWidgetItem *newItem2 = new QTableWidgetItem(it->second);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, newItem2);
    }

}
void MainWindow::on_textEdit_destroyed()
{

}


