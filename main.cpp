#include <iostream>
#include <occi.h> 


using namespace oracle::occi;
using namespace std;

bool authenticateUser(Environment* env, const string& username, const string& password) {
    Connection* conn = nullptr;
    try {
        conn = env->createConnection("sys as sysdba", "123", "localhost:1521/XEPDB1");
        Statement* stmt = conn->createStatement();
        stmt->setSQL("SELECT COUNT(*) FROM users WHERE username = :1 AND password = :2");

        stmt->setString(1, username);
        stmt->setString(2, password); //Compare Hashed passwords
        ResultSet* rs = stmt->executeQuery();

        if (rs->next() && rs->getInt(1) == 1) {
            stmt->closeResultSet(rs);
            conn->terminateStatement(stmt);
            env->terminateConnection(conn);
            return true;
        }

        stmt->closeResultSet(rs);
        conn->terminateStatement(stmt);
    } catch (SQLException& e) {
        cerr << "Authentication Error: " << e.getMessage() << endl;
    }

    if (conn) {
        env->terminateConnection(conn);
    }
    return false;
}

int main() {
    Environment* env = Environment::createEnvironment(Environment::DEFAULT);
    string username, password;

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    bool authenticated = authenticateUser(env, username, password);

    if (authenticated) {
        cout << "Login successful!" << endl;
    } else {
        cout << "Login failed!" << endl;
    }

    Environment::terminateEnvironment(env);
    return 0;
}
