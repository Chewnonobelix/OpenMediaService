#pragma once

#include <QString>

const auto libTable = QStringLiteral("CREATE TABLE `library` ("
                                     "`id` TEXT NOT NULL PRIMARY KEY,"
                                     "`name` TEXT,"
                                     "`role` INTEGER NOT NULL DEFAULT 0,"
                                     "`isShared BOOLEAN DEFAULT 0 "
                                     ")");

const auto sourceDir = QStringLiteral("CREATE TABLE `sourceDir` ("
                                      "`id` INTEGER NOT NULL PRIMARY INDEX AUTOINCREMENT,"
                                      "`lib` TEXT NOT NULL REFERENCES library(id),"
                                      "`dir` TEXT NOT NULL,"
                                      "CONSTRAINT source_unique UNIQUE(lib, dir)"
                                      ")");

const auto probe = QStringLiteral("CREATE TABLE `probe` ("
                                  "`id' INTEGER NOT NULL PRIMARY INDEX AUTOINCREMENT,"
                                  "`lib` TEXT NOT NULL REFERENCES library(id),"
                                  "`lastProbed` date DEFAULT NULL,"
                                  "CONSTRAINT probe_unique UNIQUE (lib)"
                                  ")");

const auto media = QStringLiteral("CREATE TABLE `media` ("
                                  ""
                                  ")");



