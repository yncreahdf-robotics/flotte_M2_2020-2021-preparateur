#!/usr/bin/env python

import mysql.connector


def create_Article_tb(flotte_db):
	mycursor=flotte_db.cursor()
	mycursor.execute("CREATE TABLE IF NOT EXISTS Article_tb (ArticleID INT AUTO_INCREMENT, ArticleName VARCHAR(30), ArticlePrice INT, ArticleWeight INT, Bouteille1 INT, Bouteille2 INT, Bouteille3 INT, Bouteille4 INT, Bouteille5 INT,  Bouteille6 INT,CONSTRAINT ArticleID_pk PRIMARY KEY (ArticleID))" ) 
	mycursor.close()

def check_Article_tb(flotte_db):
	mycursor=flotte_db.cursor()	
	mycursor.execute("SHOW TABLES")
	for x in mycursor:
		print(x)
	mycursor.close()


def insert_Article(flotte_db,ArticleName, ArticlePrice, ArticleWeight):
	sql="INSERT INTO Article_tb (ArticleName, ArticlePrice, ArticleWeight, Bouteille1,Bouteille2,Bouteille3,Bouteille4,Bouteille5,Bouteille6) VALUES(%s,%s,%s,%s,%s,%s,%s,%s,%s)"
	val=(ArticleName,ArticlePrice,ArticleWeight,Bouteille1,Bouteille2,Bouteille3,Bouteille4,Bouteille5,Bouteille6)
	mycursor=flotte_db.cursor()
	mycursor.execute(sql,val)
	flotte_db.commit()
	print(mycursor.rowcount,"Article ajoute au menu")

def get_all_Articles(flotte_db):
	mycursor=flotte_db.cursor()
	sql="SELECT ArticleID FROM Article_tb ORDER BY ArticleName"
	mycursor.execute(sql)
	myresult=mycursor.fetchall()
	for x in myresult:
		print(x)
	mycursor.close()

def get_Article_by_name(flotte_db, ArticleID):
	mycursor=flotte_db.cursor()
	sql = "SELECT * FROM Article_tb WHERE ArticleID= \"" + ArticleID + "\""
	mycursor.execute(sql)
	myresult = mycursor.fetchall()
	for x in myresult:
		print(x)
	mycursor.close()

def delete_Article(flotte_db, ArticleID): 
	mycursor=flotte_db.cursor()
	sql="DELETE FROM Article_tb WHERE ArticleID=" + ArticleID + "\""
	mycursor=flotte_db.cursor()
	mycursor.execute(sql)
	flotte_db.commit()
	print(mycursor.rowcount,"Article deleted")
	mycursor.close()
