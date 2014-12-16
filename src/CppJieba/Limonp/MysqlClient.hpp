#ifndef LIMONP_MYSQLCLIENT_H
#define LIMONP_MYSQLCLIENT_H

#include <mysql.h>
#include <iostream>
#include <vector>
#include <string>
#include "Logger.hpp"
#include "InitOnOff.hpp"

namespace Limonp
{
    using namespace std;
    class MysqlClient: public InitOnOff
    {
        public:
            typedef vector< vector<string> > RowsType;
        private:
            const string host_;
            const size_t port_;
            const string user_;
            const string passwd_;
            const string db_;
            const string charset_;
        public:
            MysqlClient(const string& host, size_t port, const string& user, const string& passwd, const string& db, const string& charset = "utf8"): host_(host), port_(port), user_(user), passwd_(passwd), db_(db), charset_(charset), conn_(NULL)
            {
                setInitFlag_(init_());
            }
            ~MysqlClient()
            {
                if(conn_)
                {
                    mysql_close(conn_);
                }
            };
        private:
            bool init_()
            {
                //cout<<mysql_get_client_info()<<endl;
                if(NULL == (conn_ = mysql_init(NULL)))
                {
                    LogError("mysql_init faield. %s", mysql_error(conn_));
                    return false;
                }

                if (mysql_real_connect(conn_, host_.c_str(), user_.c_str(), passwd_.c_str(), db_.c_str(), port_, NULL, 0) == NULL)
                {
                    LogError("mysql_real_connect failed. %s", mysql_error(conn_));
                    mysql_close(conn_);
                    conn_ = NULL;
                    return false;
                }  

                if(mysql_set_character_set(conn_, charset_.c_str()))
                {
                    LogError("mysql_set_character_set [%s] failed.", charset_.c_str());
                    return false;
                }

                //set reconenct
                char value = 1;
                mysql_options(conn_, MYSQL_OPT_RECONNECT, &value);

                LogInfo("MysqlClient {host: %s, database:%s, charset:%s}", host_.c_str(), db_.c_str(), charset_.c_str());
                return true;
            }
        public:
            bool executeSql(const string& sql)
            {
                assert(getInitFlag_());
                if(mysql_query(conn_, sql.c_str())) 
                {
                    LogError("mysql_query failed.  %s", mysql_error(conn_));
                    return false;
                }
                return true;
            }
            size_t insert(const string& tableName, const string& keys, const vector<string>& vals)
            {
                size_t retn = 0;
                string sql;
                for(size_t i = 0; i < vals.size(); i ++)
                {
                    sql.clear();
                    string_format(sql, "insert into %s (%s) values %s", tableName.c_str(), keys.c_str(), vals[i].c_str());
                    retn += executeSql(sql.c_str());
                }
                return retn;
            }
            bool select(const string& sql, RowsType& rows)
            {
                if(!executeSql(sql))
                {
                    LogError("executeSql failed. [%s]", sql.c_str());
                    return false;
                }
                MYSQL_RES * result = mysql_store_result(conn_);
                if(!result)
                {
                    LogError("mysql_store_result failed.[%d]", mysql_error(conn_));
                    return false;
                }
                size_t num_fields = mysql_num_fields(result);
                MYSQL_ROW row;
                while((row = mysql_fetch_row(result)))
                {
                    vector<string> vec;
                    for(size_t i = 0; i < num_fields; i ++)
                    {
                        row[i] ? vec.push_back(row[i]) : vec.push_back("NULL");
                    }
                    rows.push_back(vec);
                }
                mysql_free_result(result);
                return true;
            }

        private:
            MYSQL * conn_;

    };
}

#endif
