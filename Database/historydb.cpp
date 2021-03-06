#include "historydb.h"
#include "Singleton.h"

HistoryDB::HistoryDB()
{
    mQSqlQuery=Singleton_M::Intance().get_new_query();
}

HistoryDB::~HistoryDB()
{
    delete mQSqlQuery;
}

void HistoryDB::add_items_shop_history(const int _id_shop)
{
    mQSqlQuery->prepare("insert into t_History_purchases (DateTime, id_item, Price, Amount)"
    " select datetime('now','localtime'), id, Current_Price,Amount from t_List_Items where Amount>0 and Price>0 and id_shop=:id_shop");
    mQSqlQuery->bindValue(":id_shop", _id_shop);

    if (!mQSqlQuery->exec())
    {
        qDebug() << "Error HistoryDB::add_items_shop_history";
    }

}

void HistoryDB::null_amount_items(const int _id_shop)
{
    mQSqlQuery->prepare("UPDATE t_List_Items SET Amount=0 WHERE id_shop=:_id_shop");
    mQSqlQuery->bindValue(":_id_shop", _id_shop);

    if (!mQSqlQuery->exec())
    {
        qDebug() << "Error HistoryDB::null_amount_items";
    }

}

bool HistoryDB::getNextHistoryItem(HistoryItem& m_HistoryItem)
{
    if (!isActivatedSelectHistoryItem)
    {
        //Берутся данные за последние 24 часа
        mQSqlQuery->prepare("SELECT thp.DateTime,thp.Price,thp.Amount,tli.Name FROM t_History_purchases thp"
                            " left join t_List_Items tli on thp.id_item=tli.id"
                            " where DateTime>DATETIME(datetime('now','localtime'), '-24 hours')"
                            " order by DateTime DESC");

        if (!mQSqlQuery->exec())
        {
            qDebug() << "Error HistoryDB::getNextHistoryItem";
            return false;
        }
        rec = mQSqlQuery->record();
        isActivatedSelectHistoryItem=true;
    }

    if (mQSqlQuery->next())
    {
        m_HistoryItem.mDateTime=mQSqlQuery->value(rec.indexOf("DateTime")).toDateTime();
        m_HistoryItem.price=mQSqlQuery->value(rec.indexOf("Price")).toDouble();
        m_HistoryItem.amount=mQSqlQuery->value(rec.indexOf("Amount")).toDouble();
        m_HistoryItem.Name=mQSqlQuery->value(rec.indexOf("Name")).toString();

        return true;
    }
    isActivatedSelectHistoryItem=false;
    return false;
}
