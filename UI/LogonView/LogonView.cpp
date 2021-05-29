#include "LogonView.h"
#include <lib/Logon.h>

#include <qdebug.h>
#include <iostream>

LogonView::LogonView(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    // prepare the view
    auto tbw = this->findChild<QTableWidget*>("tableUR"); // HKCU Run
    qDebug() << "Looking\n";
    if (tbw) {
      qDebug() << "Found tableUR\n";
      tbw->setSelectionMode(QAbstractItemView::NoSelection);
      tbw->verticalHeader()->hide();
    }
    tbw = this->findChild<QTableWidget*>("tableURO"); // HKCU RunOnce
    qDebug() << "Looking\n";
    if (tbw) {
      qDebug() << "Found tableURO\n";
      tbw->setSelectionMode(QAbstractItemView::NoSelection);
      tbw->verticalHeader()->hide();
    }
    tbw = this->findChild<QTableWidget*>("tableMR"); // HKLM Run
    qDebug() << "Looking\n";
    if (tbw) {
      qDebug() << "Found tableMR\n";
      tbw->setSelectionMode(QAbstractItemView::NoSelection);
      tbw->verticalHeader()->hide();
    }
    tbw = this->findChild<QTableWidget*>("tableMRO"); // HKLM RunOnce
    qDebug() << "Looking\n";
    if (tbw) {
      qDebug() << "Found tableMRO\n";
      tbw->setSelectionMode(QAbstractItemView::NoSelection);
      tbw->verticalHeader()->hide();
    }

    // TreeView
    auto tv = this->findChild<QTreeWidget*>("treeMR");


    // HKLM Run
    vector<Logon::logon_t> logon = Logon::GetRun(HKEY_LOCAL_MACHINE);
    tbw = this->findChild<QTableWidget*>("tableMR");
    if (tbw) {
      qDebug() << "logon.size() = " << logon.size() << "\n";
      tbw->setRowCount(logon.size());
      for (int i = 0; i < logon.size(); ++i) {
        wstring e, im; DWORD v;
        std::tie(e, v, im) = logon[i];
        QString entry = QString::fromStdWString(e);
        QString verified;
        switch (v) {
        case ERROR_SUCCESS: verified = "Yes"; break;
        case TRUST_E_SUBJECT_NOT_TRUSTED: verified = "No"; break;
        default: verified = "Unknown";
        }
        QString impa = QString::fromStdWString(im);
        qDebug() << "Result: " << entry << "  " << verified << "  " << impa << "\n";
        tbw->setItem(i, 0, new QTableWidgetItem(entry));
        tbw->setItem(i, 1, new QTableWidgetItem(verified));
        tbw->setItem(i, 2, new QTableWidgetItem(impa));
      }
      tbw->resizeColumnToContents(0);
    }

    // HKCU Run
    logon = Logon::GetRun(HKEY_CURRENT_USER);
    tbw = this->findChild<QTableWidget*>("tableUR");
    if (tbw) {
      qDebug() << "logon.size() = " << logon.size() << "\n";
      tbw->setRowCount(logon.size());
      for (int i = 0; i < logon.size(); ++i) {
        wstring e, im; DWORD v;
        std::tie(e, v, im) = logon[i];
        QString entry = QString::fromStdWString(e);
        QString verified;
        switch (v) {
        case ERROR_SUCCESS: verified = "Yes"; break;
        case TRUST_E_SUBJECT_NOT_TRUSTED: verified = "No"; break;
        default: verified = "Unknown";
        }
        QString impa = QString::fromStdWString(im);
        qDebug() << "Result: " << entry << "  " << verified << "  " << impa << "\n";
        tbw->setItem(i, 0, new QTableWidgetItem(entry));
        tbw->setItem(i, 1, new QTableWidgetItem(verified));
        tbw->setItem(i, 2, new QTableWidgetItem(impa));
      }
      tbw->resizeColumnToContents(0);
    }

    // HKLM RunOnce
    logon = Logon::GetRunOnce(HKEY_LOCAL_MACHINE);
    tbw = this->findChild<QTableWidget*>("tableMRO");
    if (tbw) {
      qDebug() << "logon.size() = " << logon.size() << "\n";
      tbw->setRowCount(logon.size());
      for (int i = 0; i < logon.size(); ++i) {
        wstring e, im; DWORD v;
        std::tie(e, v, im) = logon[i];
        QString entry = QString::fromStdWString(e);
        QString verified;
        switch (v) {
        case ERROR_SUCCESS: verified = "Yes"; break;
        case TRUST_E_SUBJECT_NOT_TRUSTED: verified = "No"; break;
        default: verified = "Unknown";
        }
        QString impa = QString::fromStdWString(im);
        qDebug() << "Result: " << entry << "  " << verified << "  " << impa << "\n";
        tbw->setItem(i, 0, new QTableWidgetItem(entry));
        tbw->setItem(i, 1, new QTableWidgetItem(verified));
        tbw->setItem(i, 2, new QTableWidgetItem(impa));
      }
      tbw->resizeColumnToContents(0);
    }

    // HKCU RunOnce
    logon = Logon::GetRunOnce(HKEY_LOCAL_MACHINE);
    tbw = this->findChild<QTableWidget*>("tableURO");
    if (tbw) {
      qDebug() << "logon.size() = " << logon.size() << "\n";
      tbw->setRowCount(logon.size());
      for (int i = 0; i < logon.size(); ++i) {
        wstring e, im; DWORD v;
        std::tie(e, v, im) = logon[i];
        QString entry = QString::fromStdWString(e);
        QString verified;
        switch (v) {
        case ERROR_SUCCESS: verified = "Yes"; break;
        case TRUST_E_SUBJECT_NOT_TRUSTED: verified = "No"; break;
        default: verified = "Unknown";
        }
        QString impa = QString::fromStdWString(im);
        qDebug() << "Result: " << entry << "  " << verified << "  " << impa << "\n";
        tbw->setItem(i, 0, new QTableWidgetItem(entry));
        tbw->setItem(i, 1, new QTableWidgetItem(verified));
        tbw->setItem(i, 2, new QTableWidgetItem(impa));
      }
      tbw->resizeColumnToContents(0);
    }

    // HKLM RunOnceEX
    tv = this->findChild<QTreeWidget*>("treeMR");
    if (tv) {
      vector<Logon::roe_t> roe = Logon::GetRunOnceEx(HKEY_LOCAL_MACHINE);
      for (const auto& key : roe) {
        QTreeWidgetItem* wentry = new QTreeWidgetItem(tv);
        wentry->setText(0, QString::fromStdWString(key.first));
        for (const auto& i : key.second) {
          QTreeWidgetItem* item = new QTreeWidgetItem();
          wstring e, im; DWORD v;
          std::tie(e, v, im) = i;
          QString entry = QString::fromStdWString(e);
          QString verified;
          switch (v) {
          case ERROR_SUCCESS: verified = "Yes"; break;
          case TRUST_E_SUBJECT_NOT_TRUSTED: verified = "No"; break;
          default: verified = "Unknown";
          }
          QString impa = QString::fromStdWString(im);
          item->setText(0, entry);
          item->setText(1, verified);
          item->setText(2, impa);
          wentry->addChild(item);
        }
      }
    }

    // HKCU RunOnceEX
    tv = this->findChild<QTreeWidget*>("treeUR");
    if (tv) {
      vector<Logon::roe_t> roe = Logon::GetRunOnceEx(HKEY_CURRENT_USER);
      for (const auto& key : roe) {
        QTreeWidgetItem* wentry = new QTreeWidgetItem(tv);
        wentry->setText(0, QString::fromStdWString(key.first));
        for (const auto& i : key.second) {
          QTreeWidgetItem* item = new QTreeWidgetItem();
          wstring e, im; DWORD v;
          std::tie(e, v, im) = i;
          QString entry = QString::fromStdWString(e);
          QString verified;
          switch (v) {
          case ERROR_SUCCESS: verified = "Yes"; break;
          case TRUST_E_SUBJECT_NOT_TRUSTED: verified = "No"; break;
          default: verified = "Unknown";
          }
          QString impa = QString::fromStdWString(im);
          item->setText(0, entry);
          item->setText(1, verified);
          item->setText(2, impa);
          wentry->addChild(item);
        }
      }
    }
}

LogonView::~LogonView()
{
}
