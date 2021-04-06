#ifndef ACCUSE_H
#define ACCUSE_H
//tt
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class accuse
{
public:
    accuse();
    accuse(int,QString,QString,QString);
    int getid();
    QString getnom();
    QString getprenom();
    QString gettype();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void settype(QString);
    bool ajouter();
    bool modifier(int id,QString nom, QString prenom,QString type );
    QSqlQueryModel * rechercher(int id);
        QSqlQueryModel * afficher();
        QSqlQueryModel *Trier(QString );
        bool supprimer(int);
private:
    int id ;
    QString nom,prenom,type;
};

#endif // ACCUSE_H
