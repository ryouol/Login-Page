CREATE TABLE users (
    id NUMBER GENERATED BY DEFAULT AS IDENTITY,
    username VARCHAR2(50) NOT NULL UNIQUE,
    password VARCHAR2(50) NOT NULL,
    security_level NUMBER NOT NULL,
    PRIMARY KEY (id)
);


INSERT INTO users (username, password, security_level) VALUES ('1004', 'passwordForEngineer', 4); -- Engineer
INSERT INTO users (username, password, security_level) VALUES ('1003', 'passwordForAdmin', 3); -- Admin
INSERT INTO users (username, password, security_level) VALUES ('1002', 'passwordForManager', 2); -- Manager
INSERT INTO users (username, password, security_level) VALUES ('1001', 'passwordForStaff', 1); -- Staff
