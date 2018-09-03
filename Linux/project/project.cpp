#include <iostream>

#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QFile>

#include "project.h"

Project::Project(QObject *parent): QObject(parent) { this->currentPath = QDir::currentPath(); }

void Project::createDir() {
  QDir currentDir(this->currentPath);
  currentDir.mkdir("src");
  currentDir.mkdir("doc");
  currentDir.mkdir("build");
}

void Project::createLicence() {
  QFile licence("LICENSE");
  if (!licence.open(QFile::WriteOnly | QFile::Text)) {
    qDebug() << qPrintable(licence.errorString());
  }
  QTextStream out(&licence);
  QString content =
      "                   GNU LESSER GENERAL PUBLIC LICENSE\n                       Version 3, 29 June 2007\n\n Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>\n Everyone is permitted to copy and distribute verbatim copies\n of this license document, but changing it is not "
      "allowed.\n\n\n  This version of the GNU Lesser General Public License incorporates\nthe terms and conditions of version 3 of the GNU General Public\nLicense, supplemented by the additional permissions listed below.\n\n  0. Additional Definitions.\n\n  As used herein, \"this License\" refers "
      "to version 3 of the GNU Lesser\nGeneral Public License, and the \"GNU GPL\" refers to version 3 of the GNU\nGeneral Public License.\n\n  \"The Library\" refers to a covered work governed by this License,\nother than an Application or a Combined Work as defined below.\n\n  An \"Application\" "
      "is any work that makes use of an interface provided\nby the Library, but which is not otherwise based on the Library.\nDefining a subclass of a class defined by the Library is deemed a mode\nof using an interface provided by the Library.\n\n  A \"Combined Work\" is a work produced by "
      "combining or linking an\nApplication with the Library.  The particular version of the Library\nwith which the Combined Work was made is also called the \"Linked\nVersion\".\n\n  The \"Minimal Corresponding Source\" for a Combined Work means the\nCorresponding Source for the Combined Work, "
      "excluding any source code\nfor portions of the Combined Work that, considered in isolation, are\nbased on the Application, and not on the Linked Version.\n\n  The \"Corresponding Application Code\" for a Combined Work means the\nobject code and/or source code for the Application, including "
      "any data\nand utility programs needed for reproducing the Combined Work from the\nApplication, but excluding the System Libraries of the Combined Work.\n\n  1. Exception to Section 3 of the GNU GPL.\n\n  You may convey a covered work under sections 3 and 4 of this License\nwithout being "
      "bound by section 3 of the GNU GPL.\n\n  2. Conveying Modified Versions.\n\n  If you modify a copy of the Library, and, in your modifications, a\nfacility refers to a function or data to be supplied by an Application\nthat uses the facility (other than as an argument passed when "
      "the\nfacility is invoked), then you may convey a copy of the modified\nversion:\n\n   a) under this License, provided that you make a good faith effort to\n   ensure that, in the event an Application does not supply the\n   function or data, the facility still operates, and performs\n   "
      "whatever part of its purpose remains meaningful, or\n\n   b) under the GNU GPL, with none of the additional permissions of\n   this License applicable to that copy.\n\n  3. Object Code Incorporating Material from Library Header Files.\n\n  The object code form of an Application may "
      "incorporate material from\na header file that is part of the Library.  You may convey such object\ncode under terms of your choice, provided that, if the incorporated\nmaterial is not limited to numerical parameters, data structure\nlayouts and accessors, or small macros, inline functions "
      "and templates\n(ten or fewer lines in length), you do both of the following:\n\n   a) Give prominent notice with each copy of the object code that the\n   Library is used in it and that the Library and its use are\n   covered by this License.\n\n   b) Accompany the object code with a copy "
      "of the GNU GPL and this license\n   document.\n\n  4. Combined Works.\n\n  You may convey a Combined Work under terms of your choice that,\ntaken together, effectively do not restrict modification of the\nportions of the Library contained in the Combined Work and reverse\nengineering for "
      "debugging such modifications, if you also do each of\nthe following:\n\n   a) Give prominent notice with each copy of the Combined Work that\n   the Library is used in it and that the Library and its use are\n   covered by this License.\n\n   b) Accompany the Combined Work with a copy of "
      "the GNU GPL and this license\n   document.\n\n   c) For a Combined Work that displays copyright notices during\n   execution, include the copyright notice for the Library among\n   these notices, as well as a reference directing the user to the\n   copies of the GNU GPL and this license "
      "document.\n\n   d) Do one of the following:\n\n       0) Convey the Minimal Corresponding Source under the terms of this\n       License, and the Corresponding Application Code in a form\n       suitable for, and under terms that permit, the user to\n       recombine or relink the "
      "Application with a modified version of\n       the Linked Version to produce a modified Combined Work, in the\n       manner specified by section 6 of the GNU GPL for conveying\n       Corresponding Source.\n\n       1) Use a suitable shared library mechanism for linking with the\n       "
      "Library.  A suitable mechanism is one that (a) uses at run time\n       a copy of the Library already present on the user's computer\n       system, and (b) will operate properly with a modified version\n       of the Library that is interface-compatible with the Linked\n       Version.\n\n "
      "  e) Provide Installation Information, but only if you would otherwise\n   be required to provide such information under section 6 of the\n   GNU GPL, and only to the extent that such information is\n   necessary to install and execute a modified version of the\n   Combined Work produced by "
      "recombining or relinking the\n   Application with a modified version of the Linked Version. (If\n   you use option 4d0, the Installation Information must accompany\n   the Minimal Corresponding Source and Corresponding Application\n   Code. If you use option 4d1, you must provide the "
      "Installation\n   Information in the manner specified by section 6 of the GNU GPL\n   for conveying Corresponding Source.)\n\n  5. Combined Libraries.\n\n  You may place library facilities that are a work based on the\nLibrary side by side in a single library together with other "
      "library\nfacilities that are not Applications and are not covered by this\nLicense, and convey such a combined library under terms of your\nchoice, if you do both of the following:\n\n   a) Accompany the combined library with a copy of the same work based\n   on the Library, uncombined with "
      "any other library facilities,\n   conveyed under the terms of this License.\n\n   b) Give prominent notice with the combined library that part of it\n   is a work based on the Library, and explaining where to find the\n   accompanying uncombined form of the same work.\n\n  6. Revised "
      "Versions of the GNU Lesser General Public License.\n\n  The Free Software Foundation may publish revised and/or new versions\nof the GNU Lesser General Public License from time to time. Such new\nversions will be similar in spirit to the present version, but may\ndiffer in detail to address "
      "new problems or concerns.\n\n  Each version is given a distinguishing version number. If the\nLibrary as you received it specifies that a certain numbered version\nof the GNU Lesser General Public License \"or any later version\"\napplies to it, you have the option of following the terms "
      "and\nconditions either of that published version or of any later version\npublished by the Free Software Foundation. If the Library as you\nreceived it does not specify a version number of the GNU Lesser\nGeneral Public License, you may choose any version of the GNU Lesser\nGeneral Public "
      "License ever published by the Free Software Foundation.\n\n  If the Library as you received it specifies that a proxy can decide\nwhether future versions of the GNU Lesser General Public License shall\napply, that proxy's public statement of acceptance of any version is\npermanent "
      "authorization for you to choose that version for the\nLibrary.\n";
  out << content;
  licence.close();
}

void Project::createREADME() {
  QFile readme("README.md");
  if (!readme.open(QFile::WriteOnly | QFile::Text)) {
    qDebug() << qPrintable(readme.errorString());
  }
  readme.close();
}

void Project::createResources() {
  QFile readme("resources.qrc");
  if (!readme.open(QFile::WriteOnly | QFile::Text)) {
    qDebug() << qPrintable(readme.errorString());
  }
  readme.close();
}

void Project::createRootCMakeLists() {
  QString baseName = QDir(this->currentPath).dirName();
  QString CMakeLists = this->currentPath + "/CMakeLists.txt";
  QFile file(CMakeLists);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
    qDebug() << qPrintable(file.errorString());
  }
  QTextStream out(&file);
  QString tempContent;
  if (isQt) {
    tempContent = "set(CMAKE_AUTOMOC ON)\nset(CMAKE_AUTOUIC ON)\nset(CMAKE_AUTORCC ON)";
  } else {
    tempContent = "set(CMAKE_AUTOMOC OFF)\nset(CMAKE_AUTOUIC OFF)\nset(CMAKE_AUTORCC OFF)";
  }
  QString content =
      "# 设定需要的CMake的最小版本\ncmake_minimum_required(VERSION 2.8.11)\n\n# 设定项目的名字\nproject(" + baseName +
      ")\n\n# 一些设定\nset(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)\nset(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)\nset(CMAKE_RUNTIME_OUTPUT_DIRECTORY "
      "${CMAKE_BINARY_DIR}/bin)\n\n# 一些设定\nset(CMAKE_INCLUDE_CURRENT_DIR ON)\n" +
      tempContent +
      "\nset(CMAKE_CXX_STANDARD 11)\n\n# 查找需要的Qt模块\nfind_package(Qt5Core REQUIRED)\nfind_package(Qt5Gui REQUIRED)\nfind_package(Qt5Widgets "
      "REQUIRED)\nfind_package(Qt5Network REQUIRED)\nfind_package(Qt5OpenGL REQUIRED)\nfind_package(Qt53DCore REQUIRED)\nfind_package(Qt5PrintSupport REQUIRED)\nfind_package(Qt5WebEngine REQUIRED)\nfind_package(Qt5Xml REQUIRED)\nif(Qt5Widgets_FOUND AND Qt5Core_FOUND AND Qt5Gui_FOUND AND "
      "Qt5Network_FOUND AND Qt5OpenGL_FOUND AND Qt53DCore_FOUND AND Qt5PrintSupport_FOUND AND Qt5WebEngine_FOUND AND Qt5Xml_FOUND)\n  message(STATUS \"查找到Qt: ${Qt5Core_VERSION_STRING}\" )\nelse(Qt5Widgets_FOUND AND Qt5Core_FOUND AND Qt5Gui_FOUND AND Qt5Network_FOUND AND Qt5OpenGL_FOUND AND "
      "Qt53DCore_FOUND AND Qt5PrintSupport_FOUND AND Qt5WebEngine_FOUND AND Qt5Xml_FOUND)\n  message(WARNING \"未查找Qt\" )\nendif(Qt5Widgets_FOUND AND Qt5Core_FOUND AND Qt5Gui_FOUND AND Qt5Network_FOUND AND Qt5OpenGL_FOUND AND Qt53DCore_FOUND AND Qt5PrintSupport_FOUND AND Qt5WebEngine_FOUND AND "
      "Qt5Xml_FOUND)\n  \n# 查找需要的ROOT模块\nfind_package(ROOT REQUIRED)\nif(ROOT_FOUND)\n  message(STATUS \"查找到ROOT: ${ROOT_VERSION}\")\nelse(ROOT_FOUND)\n  message(WARNING \"未查找到ROOT\")\nendif(ROOT_FOUND)\n\n# 查找需要的OpenCV模块\nfind_package(OpenCV REQUIRED)\n\n# "
      "查找需要的Boost模块\nfind_package(Boost REQUIRED)\ninclude_directories(${Boost_INCLUDE_DIRS})\n\n################################################################################\n# "
      "添加子目录\nadd_subdirectory(src)\n\n\n################################################################################\n# 安装\ninstall(FILES LICENSE README.md\n  DESTINATION doc)\ninstall(DIRECTORY doc/\n  DESTINATION doc)\n# install(PROGRAMS test.py\n#   DESTINATION bin)\n";
  out << content;
  file.close();
}

void Project::createSrcCMakeLists() {
  QString headFiles = getFormatFiles(currentPath, ".h");
  QString srcFiles = getFormatFiles(currentPath, ".cpp");
  QString uiFiles = getFormatFiles(currentPath, ".ui");
  QString qrcFiles = getFormatFiles(currentPath, ".qrc");

  QString baseName = QDir(this->currentPath).dirName();
  QString CMakeLists = this->currentPath + "/src/CMakeLists.txt";
  QFile file(CMakeLists);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
    qDebug() << qPrintable(file.errorString());
  }
  QTextStream out(&file);
  QString content;
  if (isQt) {
    content = "# 添加源文件\nset(SRCFILES " + srcFiles + "  )\n\n# 添加头文件\nset(HEADFILES " + headFiles + "  )\n\n# 进行MOC编译\nqt5_wrap_cpp(HEAD_FILES ${HEADFILES})\n\n";
    if (!qrcFiles.isEmpty()) {
      content += "# 添加资源文件\nqt5_add_resources(QRC_FILES ${PROJECT_SOURCE_DIR}/" + qrcFiles + ")\n\n";
    }
    content +=
        "# 添加可执行文件的生成\nadd_executable(${PROJECT_NAME} ${SRCFILES} ${HEAD_FILES} ${QRC_FILES})\ntarget_link_libraries(${PROJECT_NAME}\n  ${ROOT_LIBRARIES}\n  ${OpenCV_LIBS}\n  ${Boost_LIBRARIES}\n  ${Qt5Core_LIBRARIES}\n  ${Qt5Gui_LIBRARIES}\n  ${Qt5Widgets_LIBRARIES}\n  "
        "${Qt5Network_LIBRARIES}\n  "
        "${Qt5OpenGL_LIBRARIES}\n  ${Qt53DCore_LIBRARIES}\n  ${Qt5PrintSupport_LIBRARIES}\n  ${Qt5WebEngine_LIBRARIES}\n  ${Qt5Xml_LIBRARIES})\n\n# 安装\ninstall(TARGETS ${PROJECT_NAME}\n  RUNTIME DESTINATION bin)\n# install(TARGETS ${PROJECT_NAME}\n#   LIBRARY DESTINATION lib)\n";
  } else {
    content = "# 添加源文件\nset(SRCFILES " + srcFiles + "  )\n\n# 添加头文件\nset(HEADFILES " + headFiles +
              "  )\n\n# 添加可执行文件的生成\nadd_executable(${PROJECT_NAME} ${SRCFILES} ${HEADFILES})\ntarget_link_libraries(${PROJECT_NAME}\n  ${ROOT_LIBRARIES}\n  ${OpenCV_LIBS}\n  ${Boost_LIBRARIES}\n  ${Qt5Core_LIBRARIES}\n  ${Qt5Gui_LIBRARIES}\n  ${Qt5Widgets_LIBRARIES}\n  "
              "${Qt5Network_LIBRARIES}\n  "
              "${Qt5OpenGL_LIBRARIES}\n  ${Qt53DCore_LIBRARIES}\n  ${Qt5PrintSupport_LIBRARIES}\n  ${Qt5WebEngine_LIBRARIES}\n  ${Qt5Xml_LIBRARIES})\n\n# 安装\ninstall(TARGETS ${PROJECT_NAME}\n  RUNTIME DESTINATION bin)\n# install(TARGETS ${PROJECT_NAME}\n#   LIBRARY DESTINATION lib)\n";
  }
  out << content;
  file.close();
}

void Project::setPropertity() {
  char propertity;

  while (true) {
    std::cout << "Qt Project (y or n)" << std::endl;
    std::cin >> propertity;
    if (propertity == 'Y' || propertity == 'y') {
      isQt = true;
      break;
    } else if (propertity == 'N' || propertity == 'n') {
      isQt = false;
      break;
    } else {
      std::cout << "error, please input y or n" << std::endl;
    }
  }
}

void Project::moveFile() {
  QDir currentDir(currentPath);
  QStringList files = currentDir.entryList(QDir::Files | QDir::NoDotAndDotDot);
  foreach(QString eachFile, files) {
    if (eachFile.endsWith(".cpp") || eachFile.endsWith(".h") || eachFile.endsWith(".ui")) {
      QFile::copy(eachFile, "src/" + eachFile);
      QFile::remove(eachFile);
    }
  }
}

void Project::run() {
  this->setPropertity();
  this->createDir();
  this->createLicence();
  this->createREADME();
  this->createRootCMakeLists();
  this->createSrcCMakeLists();
  this->moveFile();
}

QString Project::getFormatFiles(const QString &dirName, const QString &format) {
  QString resultFiles;

  QDir dir(dirName);
  foreach(QString eachFile, dir.entryList(QDir::Files | QDir::NoDotAndDotDot)) {
    if (eachFile.endsWith(format)) {
      resultFiles += eachFile;
      resultFiles += "  \n";
    }
  }

  return resultFiles;
}
