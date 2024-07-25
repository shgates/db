# Codd's 12 Rules for Relational Databases

Edgar Frank Codd, the pioneer of the relational model for database management, formulated a set of 12 rules to define what constitutes a truly relational database management system (RDBMS). These rules are foundational for understanding and implementing relational databases.

## 1. Information Rule
All data should be stored in tables, and all data should be accessible by table name, column name, and primary key.

## 2. Guaranteed Access Rule
Every piece of data (atomic value) should be logically accessible with a combination of table name, primary key, and column name.

## 3. Systematic Treatment of Null Values
Null values must be uniformly treated as missing information. They should be distinct from empty strings or zeroes, and their handling should be systematic across the database.

## 4. Dynamic Online Catalog Based on the Relational Model
The database schema should be stored within the database itself and should be accessible via the same query language used to access the data.

## 5. Comprehensive Data Sub-language Rule
A relational database must support a language that allows users to define data structures, manipulate data, and specify constraints. This language must support:
- Data definition
- Data manipulation
- Data integrity constraints
- Authorization

## 6. View Updating Rule
Any view that is theoretically updateable should be updateable by the system.

## 7. High-Level Insert, Update, and Delete
The system must support insert, update, and delete operations at a high level, allowing users to manipulate sets of data at a time, rather than individual rows.

## 8. Physical Data Independence
Changes to the physical level (how data is stored) should not require changes to the application or user queries.

## 9. Logical Data Independence
Changes to the logical structure (table structure) should not affect the user interface or applications. This includes adding or removing columns and tables.

## 10. Integrity Independence
Integrity constraints (such as primary keys, foreign keys, and check constraints) must be defined separately from application programs and stored in the catalog. They should be automatically enforced by the DBMS.

## 11. Distribution Independence
The user should not be aware of whether the database is distributed across multiple locations. The DBMS should manage data distribution transparently.

## 12. Non-Subversion Rule
If the system has a lower-level language, that language should not be able to bypass or subvert the integrity rules and constraints expressed in the higher-level relational language.

---

These rules ensure that a database management system adheres to the principles of the relational model, promoting consistency, integrity, and ease of use. Following these rules can help in designing robust and efficient relational databases.

