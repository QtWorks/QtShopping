#ifndef ITEMDB_H
#define ITEMDB_H

#include "commondb.h"
#include "common_struct_data.h"

class ItemDB
{
public:
    ItemDB(int m_id_Shop,int m_id_Category);
    ~ItemDB();

    void addItem(const Item& m_Item);

    void updateItem(const Item& m_Item);

    bool selectItemById(int id_Item,Item& m_Item);

    bool getNextItem(Item& m_Item);

private:
    QSqlQuery* mQSqlQuery;
    QSqlRecord rec;
    bool isActivatedSelect;

    const int id_Shop;
    const int id_Category;

};

#endif // ITEMDB_H