CREATE TABLE library ( 
	id                   TEXT NOT NULL  PRIMARY KEY  
 );

CREATE TABLE media ( 
	id                   TEXT NOT NULL  PRIMARY KEY  ,
	lib                  TEXT     ,
	FOREIGN KEY ( lib ) REFERENCES library( id )  
 );

CREATE TABLE playlist ( 
	id                   TEXT NOT NULL  PRIMARY KEY  ,
	lib                  TEXT NOT NULL    
 );

CREATE TABLE probe ( 
	lib                  TEXT NOT NULL  PRIMARY KEY  ,
	lastProbed           DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP   ,
	FOREIGN KEY ( lib ) REFERENCES library( id ) ON DELETE CASCADE ON UPDATE CASCADE
 );

CREATE TABLE sourceDir ( 
	id                   TEXT NOT NULL    ,
	path                 TEXT NOT NULL    ,
	FOREIGN KEY ( id ) REFERENCES media( id )  ,
	FOREIGN KEY ( id ) REFERENCES library( id )  
 );

CREATE UNIQUE INDEX Unq_sourceDir ON sourceDir ( id, path );

CREATE TABLE SmartGroup ( 
	id                   TEXT NOT NULL  PRIMARY KEY  ,
	op                   INTEGER     ,
	parent               TEXT     ,
	FOREIGN KEY ( parent ) REFERENCES SmartGroup( id )  ,
	FOREIGN KEY ( parent ) REFERENCES playlist( id )  
 );

CREATE TABLE SmartRule ( 
	id                   TEXT NOT NULL  PRIMARY KEY  ,
	op                   INTEGER     ,
	field                TEXT     ,
	value                TEXT     ,
	parent               TEXT     ,
	FOREIGN KEY ( parent ) REFERENCES SmartGroup( id )  
 );

CREATE TABLE mediaPlaylist ( 
	pl                   TEXT NOT NULL    ,
	media                TEXT NOT NULL    ,
	plindex              INTEGER     ,
	FOREIGN KEY ( media ) REFERENCES media( id )  ,
	FOREIGN KEY ( pl ) REFERENCES playlist( id )  
 );

CREATE TABLE metadata ( 
	id                   TEXT NOT NULL    ,
	name                 TEXT(100) NOT NULL    ,
	value                TEXT NOT NULL    ,
	FOREIGN KEY ( id ) REFERENCES library( id )  ,
	FOREIGN KEY ( id ) REFERENCES playlist( id )  
 );

CREATE UNIQUE INDEX idx_metadata ON metadata ( id, name );

CREATE TRIGGER create_library AFTER INSERT ON library
BEGIN
INSERT INTO probe (lib) VALUES (NEW.id);
INSERT INTO metadata (id, name, value) VALUES (NEW.id, "name", ""), (NEW.id, "role", 0);
END

CREATE TRIGGER delete_SmartGroup BEFORE DELETE ON SmartGroup
BEGIN
DELETE FROM SmartGroup WHERE parent=OLD.id;
DELETE FROM SmartRule WHERE parent=OLD.id;
END

CREATE TRIGGER delete_library BEFORE DELETE ON library
BEGIN
DELETE FROM sourceDir WHERE id=OLD.id;
DELETE FROM media WHERE lib=OLD.id;
DELETE FROM playlist WHERE lib=OLD.id;
DELETE FROM probe WHERE lib=OLD.id;
DELETE FROM metadata WHERE id=OLD.id;
END

CREATE TRIGGER delete_media BEFORE DELETE ON media
BEGIN
DELETE FROM mediaPlaylist WHERE media=OLD.id;
DELETE FROM metadata WHERE id=OLD.id;
DELETE FROM sourceDir WHERE id=OLD.id;
END

CREATE TRIGGER delete_playlist BEFORE DELETE ON playlist
BEGIN
DELETE FROM metadata WHERE id=OLD.id;
DELETE FROM mediaPlaylist WHERE pl=OLD.id;
DELETE FROM SmartGroup WHERE parent=OLD.id;
END
