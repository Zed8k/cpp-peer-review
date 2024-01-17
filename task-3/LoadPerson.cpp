struct DbSetingParams {

    void SetDbConector( DBLogLevel level, bool allow_exceptions ){
        db_allow_exceptions = allow_exceptions;
        db_log_level = level;
    }

    void SetDB( string_view name, int timeout ){
        db_name = name;
        db_connection_timeout = timeout;
    }

    struct Conector {
        bool is_allow_exceptions;
        DBLogLevel log_level;
    };

    Conector GetDbConector() const {
        return { db_allow_exceptions, db_log_level };
    }

    struct DB {
        string_view db_name;
        int db_connection_timeout;
    };

    DB GetDb() const {
        return { db_name, db_connection_timeout };
    }

private:
    string_view db_name;
    int db_connection_timeout;
    bool db_allow_exceptions;
    DBLogLevel db_log_level;
};

vector<Person> LoadPersons( const DbSetingParams& params
                           , int min_age
                           , int max_age
                           , string_view name_filter) {
    DBConnector connector( params.GetDbConector().is_allow_exceptions
                          , params.GetDbConector().log_level );
    DBHandler db;
    if ( params.GetDb().db_name.starts_with("tmp."s) ) {
        db = connector.ConnectTmp( params.GetDb().db_name, params.GetDb().db_connection_timeout );
    } else {
        db = connector.Connect( params.GetDb().db_name, params.GetDb().db_connection_timeout );
    }
    if (!params.GetDbConector().is_allow_exceptions && !db.IsOK()) {
        return {};
    }

    ostringstream query_str;
    query_str << "from Persons "s
              << "select Name, Age "s
              << "where Age between "s << min_age << " and "s << max_age << " "s
              << "and Name like '%"s << db.Quote(name_filter) << "%'"s;
    DBQuery query(query_str.str());

    vector<Person> persons;
    for (auto [name, age] : db.LoadRows<string, int>(query)) {
        persons.push_back({move(name), age});
    }
    return persons;
}
