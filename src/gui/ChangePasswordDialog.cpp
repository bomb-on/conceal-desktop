// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2018 The Circle Foundation & Conceal Devs
// Copyright (c) 2018-2019 Conceal Network & Conceal Devs
//  
// Copyright (c) 2018 The Circle Foundation & Conceal Devs
// Copyright (c) 2018-2019 Conceal Network & Conceal Devs
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "ChangePasswordDialog.h"
#include <QFont>
#include "Settings.h"
#include <QFontDatabase>
#include "ui_changepassworddialog.h"

namespace WalletGui {

ChangePasswordDialog::ChangePasswordDialog(QWidget* _parent) : QDialog(_parent), m_ui(new Ui::ChangePasswordDialog) {
  m_ui->setupUi(this);
  int startingFontSize = Settings::instance().getFontSize();
  setStyles(startingFontSize);
  m_ui->m_errorLabel->setText("");
  m_ui->m_newPasswordEdit->setAttribute(Qt::WA_MacShowFocusRect, 0);   
}

ChangePasswordDialog::~ChangePasswordDialog() {
}

QString ChangePasswordDialog::getNewPassword() const {
  return m_ui->m_newPasswordEdit->text();
}

QString ChangePasswordDialog::getOldPassword() const {
  return m_ui->m_oldPasswordEdit->text();
}

void ChangePasswordDialog::checkPassword(const QString& _password) {
  bool passwordIsConfirmed = !(m_ui->m_newPasswordEdit->text().trimmed().isEmpty() ||
    m_ui->m_newPasswordConfirmationEdit->text().trimmed().isEmpty() ||
    m_ui->m_newPasswordEdit->text().compare(m_ui->m_newPasswordConfirmationEdit->text()));
  m_ui->m_errorLabel->setText(passwordIsConfirmed ? "" : tr("Password not confirmed"));
  m_ui->m_okButton->setEnabled(passwordIsConfirmed);
}

void ChangePasswordDialog::setStyles(int change)
{
  /** Set the base font sizes */
  int baseFontSize = change;
  int baseTitleSize = 7 + change;
  int baseSmallButtonSize = change - 3;
  int baseLargeButtonSize = change - 1;

  int id;

  QString currentFont = Settings::instance().getFont();
  if (currentFont == "Poppins")
  {
    id = QFontDatabase::addApplicationFont(":/fonts/Poppins-Regular.ttf");
  }
  if (currentFont == "Lekton")
  {
    id = QFontDatabase::addApplicationFont(":/fonts/Lekton-Regular.ttf");
  }
  if (currentFont == "Roboto")
  {
    id = QFontDatabase::addApplicationFont(":/fonts/RobotoSlab-Regular.ttf");
  }
  if (currentFont == "Montserrat")
  {
    id = QFontDatabase::addApplicationFont(":/fonts/Montserrat-Regular.ttf");
  }
  if (currentFont == "Open Sans")
  {
    id = QFontDatabase::addApplicationFont(":/fonts/OpenSans-Regular.ttf");
  }
  if (currentFont == "Oswald")
  {
    id = QFontDatabase::addApplicationFont(":/fonts/Oswald-Regular.ttf");
  }
  if (currentFont == "Lato")
  {
    id = QFontDatabase::addApplicationFont(":/fonts/Lato-Regular.ttf");
  }

  QFont font;
  font.setFamily(currentFont);
  font.setPixelSize(baseFontSize);
  font.setLetterSpacing(QFont::PercentageSpacing, 102);
  font.setHintingPreference(QFont::PreferFullHinting);
  font.setStyleStrategy(QFont::PreferAntialias);

  QFont smallButtonFont;
  smallButtonFont.setFamily("Poppins");
  smallButtonFont.setLetterSpacing(QFont::PercentageSpacing, 102);
  smallButtonFont.setPixelSize(baseSmallButtonSize);

  QFont largeButtonFont;
  largeButtonFont.setFamily("Poppins");
  largeButtonFont.setLetterSpacing(QFont::PercentageSpacing, 102);
  largeButtonFont.setPixelSize(baseLargeButtonSize);

  QFont titleFont;
  titleFont.setFamily("Poppins");
  titleFont.setLetterSpacing(QFont::PercentageSpacing, 102);
  titleFont.setPixelSize(baseTitleSize);

  /* Create our common pool of styles */
  QString tableStyle = "QHeaderView::section{font-size:" + QString::number(baseFontSize) + "px;background-color:#282d31;color:#fff;font-weight:700;height:37px;border-top:1px solid #444;border-bottom:1px solid #444}QTreeView::item{color:#ccc;height:37px}";
  QString b1Style = "QPushButton{font-size: " + QString::number(baseLargeButtonSize) + "px; color:#fff;border:1px solid orange;border-radius:5px;} QPushButton:hover{color:orange;}";
  QString b2Style = "QPushButton{font-size: " + QString::number(baseSmallButtonSize) + "px; color: orange; border:1px solid orange; border-radius: 5px} QPushButton:hover{color: gold;}";
  QString fontStyle = "font-size:" + QString::number(baseFontSize - 1) + "px;";

  QList<QPushButton *>
      buttons = m_ui->groupBox->findChildren<QPushButton *>();
  foreach (QPushButton *button, buttons)
  {
    /* Set the font and styling for b1 styled buttons */
    if (button->objectName().contains("b1_"))
    {
      button->setStyleSheet(b1Style);
      button->setFont(largeButtonFont);
    }

    /* Set the font and styling for b2 styled buttons */
    if (button->objectName().contains("b2_"))
    {
      button->setStyleSheet(b2Style);
      button->setFont(smallButtonFont);
    }

    /* Set the font and styling for lm styled buttons */
    if (button->objectName().contains("lm_"))
    {
      button->setFont(font);
    }

    /* Set the font and styling for sm styled buttons */
    if (button->objectName().contains("sm_"))
    {
      button->setFont(font);
    }
  }

  QList<QLabel *> labels = m_ui->groupBox->findChildren<QLabel *>();
  foreach (QLabel *label, labels)
  {
    if (label->objectName().contains("title_"))
    {
      label->setFont(titleFont);
    }
    else
    {
      label->setFont(font);
    }
  }

  m_ui->groupBox->update();
}
}
