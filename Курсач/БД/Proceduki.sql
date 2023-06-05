--------------------------------------------------------
--  File created - суббота-мая-13-2023   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Procedure ADDCATEGORY
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."ADDCATEGORY" (
    category_name_in VARCHAR2
)
AS
BEGIN
    INSERT INTO "Categories" ("category_id", "category_name")
    VALUES (Categories_seq.NEXTVAL, category_name_in);
    COMMIT;
    DBMS_OUTPUT.PUT_LINE('New category ' || category_name_in || ' has been added.');
EXCEPTION
    WHEN DUP_VAL_ON_INDEX THEN
        DBMS_OUTPUT.PUT_LINE('Category ' || category_name_in || ' already exists.');
END;


/
--------------------------------------------------------
--  DDL for Procedure ADDCUSTOMER
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."ADDCUSTOMER" (
    p_first_name VARCHAR2,
    p_last_name VARCHAR2,
    p_email VARCHAR2,
    p_phone_number VARCHAR2
)
AS
BEGIN
    -- Добавляем нового клиента в таблицу "Customers" с указанными параметрами
    INSERT INTO "Customers" ("customer_id", "first_name", "last_name", "email", "phone_number")
    VALUES (Customers_seq.NEXTVAL, p_first_name, p_last_name, p_email, p_phone_number);

    -- Если добавление записи прошло успешно, выводим сообщение об успехе
    DBMS_OUTPUT.PUT_LINE('New customer ' || p_first_name || ' ' || p_last_name || ' has been added with ID ' || Customers_seq.CURRVAL || '.');
EXCEPTION
    WHEN DUP_VAL_ON_INDEX THEN
    DBMS_OUTPUT.PUT_LINE('Customer ' || p_first_name || ' ' || p_last_name || ' already exists.');
    WHEN OTHERS THEN
    -- Любые другие исключения сохраняем и выводим сообщение
    DBMS_OUTPUT.PUT_LINE('Error adding customer ' || p_first_name || ' ' || p_last_name || ': ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure ADDEMPLOYEE
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."ADDEMPLOYEE" (
    p_first_name VARCHAR2,
    p_last_name VARCHAR2,
    p_email VARCHAR2,
    p_phone_number VARCHAR2,
    p_position_id NUMBER,
    p_salary NUMBER
)
AS
    v_position_exists NUMBER;
BEGIN
    -- Проверяем существование должности с указанным идентификатором в таблице "Positions"
    SELECT COUNT(*) INTO v_position_exists FROM "Positions" WHERE "position_id" = p_position_id;

    -- Если должность не существует, выводим сообщение об ошибке
    IF v_position_exists = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Position with ID ' || p_position_id || ' does not exist.');
        RETURN;
    END IF;

    -- Добавляем нового сотрудника в таблицу "Employees" с указанными параметрами
    INSERT INTO "Employees" ("employee_id", "first_name", "last_name", "email", "phone_number", "position", "salary")
    VALUES(Employees_seq.NEXTVAL, p_first_name, p_last_name, p_email, p_phone_number, p_position_id, p_salary);
    COMMIT;
    DBMS_OUTPUT.PUT_LINE('New employee ' || p_first_name || ' ' || p_last_name || ' has been added with ID ' || Employees_seq.CURRVAL || '.');
    EXCEPTION
    WHEN DUP_VAL_ON_INDEX THEN
    DBMS_OUTPUT.PUT_LINE('Employee ' || p_first_name || ' ' || p_last_name || ' already exists.');
    WHEN OTHERS THEN
    -- Любые другие исключения сохраняем и выводим сообщение
    DBMS_OUTPUT.PUT_LINE('Error adding employee ' || p_first_name || ' ' || p_last_name || ': ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure ADDORDER
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."ADDORDER" (
   
    p_order_date DATE,
    p_status VARCHAR2,
    p_customer_id NUMBER,
    p_product_id NUMBER,
    p_quantity NUMBER
)
AS
BEGIN
     INSERT INTO "Orders" ("order_id",  "order_date", "status", "customer_id", "product_id", "quantity")
     VALUES (Orders_seq.NEXTVAL,  p_order_date, p_status, p_customer_id, p_product_id, p_quantity);
     COMMIT;
     DBMS_OUTPUT.PUT_LINE('Order has been added successfully.');
EXCEPTION
     WHEN NO_DATA_FOUND THEN
          ROLLBACK;
          DBMS_OUTPUT.PUT_LINE('Customer or Product with provided IDs does not exist.');
     WHEN OTHERS THEN
          ROLLBACK;
          DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
          
END;

/
--------------------------------------------------------
--  DDL for Procedure ADDPOSITION
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."ADDPOSITION" (
    position_name_in VARCHAR2
)
AS
BEGIN
    INSERT INTO "Positions" ("position_id", "position_name")
    VALUES (Positions_seq.NEXTVAL, position_name_in);
    COMMIT;
    DBMS_OUTPUT.PUT_LINE('New position ' || position_name_in || ' has been added.');
EXCEPTION
    WHEN DUP_VAL_ON_INDEX THEN
        DBMS_OUTPUT.PUT_LINE('Position ' || position_name_in || ' already exists.');
END;

/
--------------------------------------------------------
--  DDL for Procedure ADDPRODUCT
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."ADDPRODUCT" (
    p_product_name VARCHAR2,
    p_category_id NUMBER,
    p_price NUMBER,
    p_quantity NUMBER,
    p_storage_location VARCHAR2,
    p_img_path VARCHAR2
)
AS
    v_blob blob;
    v_bfile bfile;
    v_desOffset INTEGER := 1;
    v_srcOffset INTEGER := 1;
    v_lobMaxSize CONSTANT INT := DBMS_LOB.LOBMAXSIZE;
BEGIN
    INSERT INTO "Products" ("product_id", "product_name", "category", "price", "quantity", "storage_location", "image")
    VALUES (Products_seq.NEXTVAL, p_product_name, p_category_id, p_price, p_quantity, p_storage_location, empty_blob ())
    RETURN "image" INTO v_blob;
      v_bfile := BFILENAME('IMAGE_BASE', p_img_path);
      DBMS_LOB.FILEOPEN(v_bfile,DBMS_LOB.FILE_READONLY);
      DBMS_LOB.LOADBLOBFROMFILE(v_blob,v_bfile,v_lobMaxSize,v_desOffset,v_srcOffset);
      DBMS_LOB.FILECLOSE(v_bfile);
  COMMIT;
EXCEPTION
  WHEN OTHERS THEN
    ROLLBACK;
    DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure ADDREVIEW
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."ADDREVIEW" (
    p_customer_id NUMBER,
    p_product_id NUMBER,
    p_rating NUMBER,
    p_comment VARCHAR2 DEFAULT NULL,
    p_review_date DATE DEFAULT SYSDATE,
    p_image_path VARCHAR2 DEFAULT NULL,
    p_review_id OUT NUMBER
)
AS
    v_blob blob;
    v_bfile bfile;
    v_desOffset INTEGER := 1;
    v_srcOffset INTEGER := 1;
    v_lobMaxSize CONSTANT INT := DBMS_LOB.LOBMAXSIZE;
BEGIN
    INSERT INTO "Reviews"("review_id", "customer_id", "product_id", "rating", "comment", "review_date", "image")
    VALUES(Review_seq.NEXTVAL, p_customer_id, p_product_id, p_rating, p_comment, p_review_date, empty_blob ())
    RETURN "image" INTO v_blob;
          v_bfile := BFILENAME('IMAGE_BASE', p_image_path);
          DBMS_LOB.FILEOPEN(v_bfile,DBMS_LOB.FILE_READONLY);
          DBMS_LOB.LOADBLOBFROMFILE(v_blob,v_bfile,v_lobMaxSize,v_desOffset,v_srcOffset);
          DBMS_LOB.FILECLOSE(v_bfile);
  COMMIT;
    COMMIT;
    DBMS_OUTPUT.PUT_LINE('Review with ID ' || p_review_id || ' has been added successfully');
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Customer or product with provided IDs does not exist.');
    WHEN OTHERS THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END;

/

  GRANT EXECUTE ON "PIA"."ADDREVIEW" TO "USERKA";
  GRANT DEBUG ON "PIA"."ADDREVIEW" TO "USERKA";
--------------------------------------------------------
--  DDL for Procedure ADDTOCART
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."ADDTOCART" (
    p_customer_id IN NUMBER,
    p_product_id IN NUMBER,
    p_quantity IN NUMBER
)
IS
BEGIN
    INSERT INTO "Cart" ("cart_id", "customer_id", "product_id", "quantity")
    VALUES (Cart_seq.NEXTVAL, p_customer_id, p_product_id, p_quantity);

    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Ошибка: ' || SQLCODE || ' ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure COMPLETEORDER
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."COMPLETEORDER" (
    p_order_id IN NUMBER,
    p_salesperson_id IN NUMBER
)
IS
    v_quantity NUMBER;
    v_customer_id NUMBER;
    v_product_id NUMBER;
BEGIN
    -- Получение количества, идентификатора клиента и идентификатора продукта
    SELECT "quantity", "customer_id", "product_id"
    INTO v_quantity, v_customer_id, v_product_id
    FROM "Orders"
    WHERE "order_id" = p_order_id;

    -- Обновление статуса заказа
    UPDATE "Orders"
    SET "status" = 'Выполнено'
    WHERE "order_id" = p_order_id;

    -- Вставка записи в таблицу Sales
    INSERT INTO "Sales" ("sale_id", "sale_date", "quantity", "customer_id", "product_id", "salesperson_id")
    VALUES (Sales_seq.NEXTVAL, SYSDATE, v_quantity, v_customer_id, v_product_id, p_salesperson_id);

    COMMIT;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Заказ ' || p_order_id || ' не найден');
    WHEN OTHERS THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Ошибка: ' || SQLCODE || ' ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure DELETECARTITEMBYID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."DELETECARTITEMBYID" (
    p_cart_item_id NUMBER
)
AS 
BEGIN
    DELETE FROM "Cart" WHERE "cart_id" = p_cart_item_id;
    DBMS_OUTPUT.PUT_LINE('Cart item with ID ' || p_cart_item_id || ' has been deleted successfully.');
    COMMIT;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Cart item with ID ' || p_cart_item_id || ' does not exist.');
    WHEN OTHERS THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure DELETECATEGORY
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."DELETECATEGORY" (
    id_in NUMBER
)
AS
BEGIN
    DELETE FROM "Categories"
    WHERE "category_id" = id_in;
    COMMIT;
    DBMS_OUTPUT.PUT_LINE('Category ' || id_in || ' has been deleted.');
END;

/
--------------------------------------------------------
--  DDL for Procedure DELETECUSTOMER
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."DELETECUSTOMER" (
    p_customer_id NUMBER
)
AS
BEGIN
-- Удаляем клиента из таблицы "Customers" по его ID
DELETE FROM "Customers" WHERE "customer_id" = p_customer_id;
-- Если удаление записи прошло успешно, выводим сообщение об успехе
DBMS_OUTPUT.PUT_LINE('Customer with ID ' || p_customer_id || ' has been deleted.');
EXCEPTION
WHEN NO_DATA_FOUND THEN
DBMS_OUTPUT.PUT_LINE('Customer with ID ' || p_customer_id || ' not found.');
WHEN OTHERS THEN
-- Любые другие исключения сохраняем и выводим сообщение
DBMS_OUTPUT.PUT_LINE('Error deleting customer with ID ' || p_customer_id || ': ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure DELETEEMPLOYEE
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."DELETEEMPLOYEE" (
    employee_id_in IN NUMBER
)
AS
BEGIN
    DELETE FROM "Employees"
    WHERE "employee_id" = employee_id_in;
    COMMIT;

    DBMS_OUTPUT.PUT_LINE('Employee with ID ' || employee_id_in || ' has been deleted.');
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Employee with ID ' || employee_id_in || ' not found.');
END;

/
--------------------------------------------------------
--  DDL for Procedure DELETEFROMCART
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."DELETEFROMCART" (
    p_cart_id IN NUMBER
)
IS
BEGIN
    DELETE FROM "Cart"
    WHERE "cart_id" = p_cart_id;

    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Ошибка: ' || SQLCODE || ' ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure DELETEORDERBYID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."DELETEORDERBYID" (
    p_order_id NUMBER
)
AS 
BEGIN
    DELETE FROM "Orders" WHERE "order_id" = p_order_id;
    DBMS_OUTPUT.PUT_LINE('Order with ID ' || p_order_id || ' has been deleted successfully.');
    COMMIT;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Order with ID ' || p_order_id || ' does not exist.');
    WHEN OTHERS THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure DELETEPOSITION
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."DELETEPOSITION" (
id_in NUMBER
)
AS
BEGIN
DELETE FROM "Positions"
WHERE "position_id"=id_in;
COMMIT;
DBMS_OUTPUT.PUT_LINE('Position with ID ' || id_in || ' has been deleted.');
EXCEPTION
WHEN NO_DATA_FOUND THEN
DBMS_OUTPUT.PUT_LINE('Position with ID ' || id_in || ' does not exist.');
END;

/
--------------------------------------------------------
--  DDL for Procedure DELETEPRODUCTBYID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."DELETEPRODUCTBYID" (
    p_product_id NUMBER
)
AS 
BEGIN
    DELETE FROM "Products" WHERE "product_id" = p_product_id;
    DBMS_OUTPUT.PUT_LINE('Product with ID ' || p_product_id || ' has been deleted successfully.');
    COMMIT;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Product with ID ' || p_product_id || ' does not exist.');
    WHEN OTHERS THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure DELETEREVIEWBYID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."DELETEREVIEWBYID" (
    p_review_id NUMBER
)
AS
BEGIN
    DELETE FROM "Reviews" WHERE "review_id" = p_review_id;
    COMMIT;
    DBMS_OUTPUT.PUT_LINE('Review with ID ' || p_review_id || ' has been deleted successfully.');
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Review with ID ' || p_review_id || ' does not exist.');
    WHEN OTHERS THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure EDITCART
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."EDITCART" (
    p_cart_id IN NUMBER,
    p_quantity IN NUMBER
)
IS
BEGIN
    UPDATE "Cart"
    SET "quantity" = p_quantity
    WHERE "cart_id" = p_cart_id;

    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Ошибка: ' || SQLCODE || ' ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure EDITCATEGORYNAME
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."EDITCATEGORYNAME" (
    id_in NUMBER,
    name_in VARCHAR2
)
AS
BEGIN
    UPDATE "Categories"
    SET "category_name" = name_in
    WHERE "category_id" = id_in;
    COMMIT;
    DBMS_OUTPUT.PUT_LINE('Category ' || id_in || ' has been updated to ' || name_in || '.');
END;

/
--------------------------------------------------------
--  DDL for Procedure FILL_CATEGORIES_TABLE
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."FILL_CATEGORIES_TABLE" 
AS 
BEGIN 
    FOR i IN 1..100000 LOOP 
        INSERT INTO PIA."Categories" ("category_name","category_id") VALUES ('Category ' || i, i); 
    END LOOP; 
    COMMIT; 
END;

/
--------------------------------------------------------
--  DDL for Procedure GETALLCATEGORIES
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETALLCATEGORIES" (
categories_out OUT SYS_REFCURSOR
)
IS
BEGIN
OPEN categories_out FOR
SELECT "category_id", "category_name"
FROM "Categories";
END;

/
--------------------------------------------------------
--  DDL for Procedure GETALLCUSTOMERS
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETALLCUSTOMERS" (
    p_result OUT SYS_REFCURSOR
)
AS
BEGIN
    -- Получаем все данные о клиентах из таблицы "Customers" и передаем результат в курсор OUT-параметр
    OPEN p_result FOR
    SELECT * FROM "Customers";
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('No customers found in database.');
    WHEN OTHERS THEN
        -- Любые другие исключения сохраняем и выводим сообщение
        DBMS_OUTPUT.PUT_LINE('Error getting all customers: ' || SQLERRM);
END;


/
--------------------------------------------------------
--  DDL for Procedure GETALLEMPLOYEES
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETALLEMPLOYEES" (
    employees_out OUT SYS_REFCURSOR
)
IS 
BEGIN
    OPEN employees_out FOR 
    SELECT "employee_id", "first_name", "last_name", "email", "phone_number", "position", "salary"
    FROM "Employees";
END;


/
--------------------------------------------------------
--  DDL for Procedure GETALLORDERS
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETALLORDERS" (
    orders_out OUT SYS_REFCURSOR
)
AS 
BEGIN
    OPEN orders_out FOR 
    SELECT "order_id", "order_date", "status", "customer_id", "product_id", "quantity"
    FROM "Orders";
END;

/

  GRANT EXECUTE ON "PIA"."GETALLORDERS" TO "USERROLE";
  GRANT EXECUTE ON "PIA"."GETALLORDERS" TO "USERKA";
--------------------------------------------------------
--  DDL for Procedure GETALLPOSITIONS
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETALLPOSITIONS" (
    positions_out OUT SYS_REFCURSOR
)
IS 
BEGIN
    OPEN positions_out FOR 
    SELECT "position_id", "position_name"
    FROM "Positions";
END;

/
--------------------------------------------------------
--  DDL for Procedure GETALLPRODUCTS
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETALLPRODUCTS" (
    products_out OUT SYS_REFCURSOR
)
IS 
BEGIN
    OPEN products_out FOR 
    SELECT "product_id", "product_name", "category", "price", "quantity", "storage_location", "image"
    FROM "Products";
END;

/
--------------------------------------------------------
--  DDL for Procedure GETCARTINFOBYCUSTOMERID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETCARTINFOBYCUSTOMERID" (p_customer_id NUMBER) as
  cursor cart_info_cursor is
    select "cart_id", "customer_id", "product_id", "quantity"
    from "Cart"
    where "customer_id" = p_customer_id;
begin
  dbms_output.put_line('CART INFO FOR CUSTOMER ID ' || p_customer_id || ':');
  dbms_output.put_line('---------------------------');
  
  for cart_row in cart_info_cursor loop
    dbms_output.put_line(
      'Cart ID: ' || cart_row."cart_id" || 
      ' | Customer ID: ' || cart_row."customer_id" || 
      ' | Product ID: ' || cart_row."product_id" || 
      ' | Quantity: ' || cart_row."quantity"
    );
  end loop;
  
  dbms_output.put_line('---------------------------');
end;

/

  GRANT DEBUG ON "PIA"."GETCARTINFOBYCUSTOMERID" TO "USERROLE";
  GRANT EXECUTE ON "PIA"."GETCARTINFOBYCUSTOMERID" TO "USERROLE";
--------------------------------------------------------
--  DDL for Procedure GETCATEGORYBYID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETCATEGORYBYID" (
    id_in NUMBER, 
    category_out OUT SYS_REFCURSOR
)
IS 
BEGIN
    OPEN category_out FOR 
    SELECT "category_id", "category_name"
    FROM "Categories"
    WHERE "category_id" = id_in;
END;

/
--------------------------------------------------------
--  DDL for Procedure GETCUSTOMER
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETCUSTOMER" (
p_customer_id NUMBER,
p_result OUT SYS_REFCURSOR
)
AS
BEGIN
-- Получаем данные о клиенте по его ID и передаем результат в курсор OUT-параметр
OPEN p_result FOR
SELECT * FROM "Customers" WHERE "customer_id" = p_customer_id;
EXCEPTION
WHEN NO_DATA_FOUND THEN
DBMS_OUTPUT.PUT_LINE('Customer with ID ' || p_customer_id || ' not found.');
WHEN OTHERS THEN
-- Любые другие исключения сохраняем и выводим сообщение
DBMS_OUTPUT.PUT_LINE('Error getting customer with ID ' || p_customer_id || ': ' || SQLERRM);
END;

/

  GRANT EXECUTE ON "PIA"."GETCUSTOMER" TO "USERKA" WITH GRANT OPTION;
  GRANT DEBUG ON "PIA"."GETCUSTOMER" TO "USERKA" WITH GRANT OPTION;
--------------------------------------------------------
--  DDL for Procedure GETORDERINFOBYORDERID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETORDERINFOBYORDERID" (p_order_id NUMBER) as
  cursor order_info_cursor is
    select "order_id", "order_date", "status", "customer_id", "product_id", "quantity"
    from "Orders"
    where "order_id" = p_order_id;
begin
    dbms_output.put_line('INFO FOR ORDER ID ' || p_order_id || ':');
    dbms_output.put_line('---------------------------');
    for ord in order_info_cursor loop
        dbms_output.put_line(
            'Order ID: ' || ord."order_id" || 
            ' | Order Date: ' || to_char(ord."order_date", 'MM/DD/YYYY') ||
            ' | Status: ' || ord."status" || 
            ' | Customer ID: ' || ord."customer_id" || 
            ' | Product ID: ' || ord."product_id" || 
            ' | Quantity: ' || ord."quantity"
        );
    end loop;
    dbms_output.put_line('---------------------------');
END;

/

  GRANT EXECUTE ON "PIA"."GETORDERINFOBYORDERID" TO "USERROLE";
  GRANT DEBUG ON "PIA"."GETORDERINFOBYORDERID" TO "USERROLE";
  GRANT EXECUTE ON "PIA"."GETORDERINFOBYORDERID" TO "USERKA";
  GRANT DEBUG ON "PIA"."GETORDERINFOBYORDERID" TO "USERKA";
--------------------------------------------------------
--  DDL for Procedure GETORDERSBYCUSTOMERID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETORDERSBYCUSTOMERID" (p_customer_id NUMBER) as
  cursor orders_cursor is
    select "order_id", "order_date", "status", "customer_id", "product_id", "quantity"
    from "Orders"
    where "customer_id" = p_customer_id;
begin
    dbms_output.put_line('ORDERS FOR CUSTOMER ID ' || p_customer_id || ':');
    dbms_output.put_line('---------------------------');
    for ord in orders_cursor loop
        dbms_output.put_line(
            'Order ID: ' || ord."order_id" || 
            ' | Order Date: ' || to_char(ord."order_date", 'MM/DD/YYYY') ||
            ' | Status: ' || ord."status" || 
            ' | Customer ID: ' || ord."customer_id" || 
            ' | Product ID: ' || ord."product_id" || 
            ' | Quantity: ' || ord."quantity"
        );
    end loop;
    dbms_output.put_line('---------------------------');
END;

/

  GRANT EXECUTE ON "PIA"."GETORDERSBYCUSTOMERID" TO "USERKA";
  GRANT DEBUG ON "PIA"."GETORDERSBYCUSTOMERID" TO "USERKA";
--------------------------------------------------------
--  DDL for Procedure GETPOSITIONBYID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETPOSITIONBYID" (
    id_in NUMBER, 
    position_out OUT SYS_REFCURSOR
)
IS 
BEGIN
    OPEN position_out FOR 
    SELECT "position_id", "position_name"
    FROM "Positions"
    WHERE "position_id" = id_in;
END;

/
--------------------------------------------------------
--  DDL for Procedure GETPRODUCTBYID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETPRODUCTBYID" (
    p_product_id NUMBER,
    product_out OUT SYS_REFCURSOR
)
AS 
BEGIN
    OPEN product_out FOR 
    SELECT "product_id", "product_name", "category", "price", "quantity", "storage_location", "image"
    FROM "Products"
    WHERE "product_id" = p_product_id;
END;

/
--------------------------------------------------------
--  DDL for Procedure GETREVIEWSBYCUSTOMERID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETREVIEWSBYCUSTOMERID" (p_customer_id NUMBER) as
  cursor review_cursor is
    select *
    from "Reviews"
    where "customer_id" = p_customer_id;
begin
    dbms_output.put_line('REVIEWS FOR CUSTOMER ID ' || p_customer_id || ':');
    dbms_output.put_line('---------------------------');
    for review_row in review_cursor loop
        dbms_output.put_line(
            'Review ID:' || review_row."review_id" || 
            ' | Product ID:' || review_row."product_id" || 
            ' | Customer ID:' || review_row."customer_id" ||
            ' | Rating:' || review_row."rating" || 
            ' | Review comment:' || review_row."comment"
        );
    end loop;
    dbms_output.put_line('---------------------------');
END;

/

  GRANT EXECUTE ON "PIA"."GETREVIEWSBYCUSTOMERID" TO "USERKA";
  GRANT DEBUG ON "PIA"."GETREVIEWSBYCUSTOMERID" TO "USERKA";
--------------------------------------------------------
--  DDL for Procedure GETREVIEWSBYPRODUCTID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETREVIEWSBYPRODUCTID" (
    p_product_id NUMBER,
    review_out OUT SYS_REFCURSOR
)
AS
BEGIN
    OPEN review_out FOR
    SELECT * FROM "Reviews" WHERE "product_id" = p_product_id;
END;

/
--------------------------------------------------------
--  DDL for Procedure GETSALESBYCUSTOMERID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETSALESBYCUSTOMERID" (p_customer_id NUMBER) as
  cursor sales_cursor is
    select "sale_id", "quantity", "sale_date", "customer_id", "product_id", "salesperson_id"
    from "Sales"
    where "customer_id" = p_customer_id
    order by "sale_date" desc;
begin
    dbms_output.put_line('SALES FOR CUSTOMER ID ' || p_customer_id || ':');
    dbms_output.put_line('---------------------------');
    for sales_row in sales_cursor loop
        dbms_output.put_line(
'Sale ID: ' || sales_row."sale_id" ||
' | Quantity: ' || sales_row."quantity" ||
' | Sale Date: ' || to_char(sales_row."sale_date", 'MM/DD/YYYY') ||
' | Customer ID: ' || sales_row."customer_id" ||
' | Product ID: ' || sales_row."product_id" ||
' | Salesperson ID: ' || sales_row."salesperson_id"
);
end loop;
dbms_output.put_line('---------------------------');
END;

/

  GRANT EXECUTE ON "PIA"."GETSALESBYCUSTOMERID" TO "USERKA";
  GRANT DEBUG ON "PIA"."GETSALESBYCUSTOMERID" TO "USERKA";
--------------------------------------------------------
--  DDL for Procedure GETSALESBYPRODUCTID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."GETSALESBYPRODUCTID" (
    p_product_id IN NUMBER,
    sales_out OUT SYS_REFCURSOR
)
IS
BEGIN
    OPEN sales_out FOR 
    SELECT "sale_id", "quantity", "sale_date", "customer_id", "product_id", "salesperson_id" 
    FROM "Sales"
    WHERE "product_id" = p_product_id
    ORDER BY "sale_date" DESC;
END;

/
--------------------------------------------------------
--  DDL for Procedure INSERTPRODUCT
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."INSERTPRODUCT" (
    p_product_name VARCHAR2,
    p_category_id NUMBER,
    p_price NUMBER,
    p_quantity NUMBER,
    p_storage_location VARCHAR2,
    p_img_path VARCHAR2
)
AS
    v_blob blob;
    v_bfile bfile;
    v_desOffset INTEGER := 1;
    v_srcOffset INTEGER := 1;
    v_lobMaxSize CONSTANT INT := DBMS_LOB.LOBMAXSIZE;
BEGIN
    INSERT INTO "Products" ("product_id", "product_name", "category", "price", "quantity", "storage_location", "image")
    VALUES (Products_seq.NEXTVAL, p_product_name, p_category_id, p_price, p_quantity, p_storage_location, empty_blob ())
    RETURN "image" INTO v_blob;
      v_bfile := BFILENAME('IMAGE_BASE','test.jpg');
      DBMS_LOB.FILEOPEN(v_bfile,DBMS_LOB.FILE_READONLY);
      DBMS_LOB.LOADBLOBFROMFILE(v_blob,v_bfile,v_lobMaxSize,v_desOffset,v_srcOffset);
      DBMS_LOB.FILECLOSE(v_bfile);
  COMMIT;
EXCEPTION
  WHEN OTHERS THEN
    ROLLBACK;
    DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure MOVECARTTOORDERS
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."MOVECARTTOORDERS" (
    p_customer_id IN NUMBER
)
IS
    v_order_id NUMBER;
BEGIN
    -- Получение идентификатора для нового заказа
    SELECT ORDERS_SEQ.NEXTVAL INTO v_order_id FROM dual;

    -- Вставка записей в таблицу Orders
    INSERT INTO "Orders" ("order_id", "order_date", "status", "customer_id", "product_id", "quantity")
    SELECT ORDERS_SEQ.NEXTVAL, SYSDATE, 'начато', p_customer_id, "product_id", "quantity" 
    FROM "Cart"
    WHERE "customer_id" = p_customer_id;

    DELETE FROM "Cart" WHERE "customer_id" = p_customer_id;

    COMMIT;

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Записи в таблице Cart для клиента с id ' || p_customer_id || ' не найдены');
    WHEN OTHERS THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Ошибка: ' || SQLCODE || ' ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure UPDATECUSTOMER
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."UPDATECUSTOMER" (
    p_customer_id NUMBER,
    p_first_name VARCHAR2,
    p_lastname VARCHAR2,
    p_last_name VARCHAR2,
    p_email VARCHAR2,
    p_phone_number VARCHAR2
)
AS
BEGIN
    -- Обновляем данные клиента в таблице "Customers" по его ID
    UPDATE "Customers" SET "first_name" = p_first_name, "last_name" = p_last_name, "email" = p_email, "phone_number" = p_phone_number WHERE "customer_id" = p_customer_id;
    -- Если обновление записи прошло успешно, выводим сообщение об успехе
    DBMS_OUTPUT.PUT_LINE('Customer with ID ' || p_customer_id || ' has been updated.');
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Customer with ID ' || p_customer_id || ' not found.');
    WHEN OTHERS THEN
        -- Любые другие исключения сохраняем и выводим сообщение
        DBMS_OUTPUT.PUT_LINE('Error updating customer with ID ' || p_customer_id || ': ' || SQLERRM);
END;

/

  GRANT EXECUTE ON "PIA"."UPDATECUSTOMER" TO "USERKA";
  GRANT DEBUG ON "PIA"."UPDATECUSTOMER" TO "USERKA";
--------------------------------------------------------
--  DDL for Procedure UPDATEEMPLOYEEBYID
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."UPDATEEMPLOYEEBYID" (
    p_employee_id NUMBER,
    p_first_name VARCHAR2,
    p_last_name VARCHAR2,
    p_email VARCHAR2,
    p_phone_number VARCHAR2,
    p_position_id NUMBER,
    p_salary NUMBER
)
AS
    v_position_exists NUMBER;

BEGIN
    -- Проверяем существование должности с указанным идентификатором в таблице "Positions"
    SELECT COUNT(*) INTO v_position_exists FROM "Positions" WHERE "position_id" = p_position_id;

    -- Если должность не существует, выводим сообщение об ошибке
    IF v_position_exists = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Position with ID ' || p_position_id || ' does not exist.');
        RETURN;
    END IF;

    -- Обновляем сотрудника по указанному идентификатору
    UPDATE "Employees"
    SET "first_name" = p_first_name,
    "last_name" = p_last_name,
    "email" = p_email,
    "phone_number" = p_phone_number,
    "position" = p_position_id,
    "salary" = p_salary
    WHERE "employee_id" = p_employee_id;

    IF SQL%ROWCOUNT = 1 THEN
    DBMS_OUTPUT.PUT_LINE('Employee with ID ' || p_employee_id || ' has been updated.');
ELSE
    DBMS_OUTPUT.PUT_LINE('Employee with ID ' || p_employee_id || ' not found.');
END IF;
EXCEPTION
WHEN NO_DATA_FOUND THEN
DBMS_OUTPUT.PUT_LINE('Employee with ID ' || p_employee_id || ' not found.');
WHEN OTHERS THEN
-- Любые другие исключения сохраняем и выводим сообщение
DBMS_OUTPUT.PUT_LINE('Error updating employee with ID ' || p_employee_id || ': ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure UPDATEORDERSTATUS
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."UPDATEORDERSTATUS" (
    p_order_id NUMBER,
    p_new_status VARCHAR2
)
AS 
BEGIN
    UPDATE "Orders" SET "status" = p_new_status WHERE "order_id" = p_order_id;
    COMMIT;
    DBMS_OUTPUT.PUT_LINE('Order with ID ' || p_order_id || ' has been updated successfully.');
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Order with ID ' || p_order_id || ' does not exist.');
    WHEN OTHERS THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END;

/
--------------------------------------------------------
--  DDL for Procedure UPDATEPOSITION
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."UPDATEPOSITION" (
    id_in NUMBER,
    position_name_in VARCHAR2
)
AS
BEGIN
    UPDATE "Positions"
    SET "position_name"=position_name_in
    WHERE "position_id"=id_in;
    COMMIT;
    DBMS_OUTPUT.PUT_LINE('Position with ID ' || id_in || ' has been updated.');
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Position with ID ' || id_in || ' does not exist.');
END;

/
--------------------------------------------------------
--  DDL for Procedure UPDATEPRODUCT
--------------------------------------------------------
set define off;

  CREATE OR REPLACE NONEDITIONABLE PROCEDURE "PIA"."UPDATEPRODUCT" (
    p_product_id NUMBER,
    p_product_name VARCHAR2,
    p_category_id NUMBER,
    p_price NUMBER,
    p_quantity NUMBER,
    p_storage_location VARCHAR2,
    p_img_path VARCHAR2
)
AS
    v_blob blob;
    v_bfile bfile;
    v_desOffset INTEGER := 1;
    v_srcOffset INTEGER := 1;
    v_lobMaxSize CONSTANT INT := DBMS_LOB.LOBMAXSIZE;
BEGIN
    UPDATE "Products"
    SET "product_name" = p_product_name,
        "category" = p_category_id,
        "price" = p_price,
        "quantity" = p_quantity,
        "storage_location" = p_storage_location,
        "image" = empty_blob ()
    WHERE "product_id" = p_product_id
    RETURN "image" INTO v_blob;

    v_bfile := BFILENAME('IMAGE_BASE', p_img_path);
    DBMS_LOB.FILEOPEN(v_bfile, DBMS_LOB.FILE_READONLY);
    DBMS_LOB.LOADBLOBFROMFILE(v_blob, v_bfile, v_lobMaxSize, v_desOffset, v_srcOffset);
    DBMS_LOB.FILECLOSE(v_bfile);

    COMMIT;

    DBMS_OUTPUT.PUT_LINE('Product with ID ' || p_product_id || ' has been updated successfully.');

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Product with ID ' || p_product_id || ' does not exist.');
    WHEN OTHERS THEN
        ROLLBACK;
        DBMS_OUTPUT.PUT_LINE('Error: ' || SQLERRM);
END;

/
