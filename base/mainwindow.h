#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "../base/controlconfig.h"

// forwards
namespace Ui {
	class MainWindow;
	class Frame_Clubs;
}
namespace Ipponboard
{
	class View;
	class Controller;
	class ClubManager;
	class FightCategoryMgr;
	class ScoreScreen;
}

namespace FMlib {
	class Gamepad;
}
typedef boost::shared_ptr<FMlib::Gamepad> PGamePad;

#ifdef TEAM_VIEW
	static const char* const str_ini_name = "IpponboardT.ini";
	static const char* const str_mode_1te_bundesliga_nord = "1. Bundesliga - Gruppe Nord";
	static const char* const str_mode_1te_bundesliga_sued = "1. Bundesliga - Gruppe S�d";
	static const char* const str_mode_2te_bundesliga_nord = "2. Bundesliga - Gruppe Nord";
	static const char* const str_mode_2te_bundesliga_sued = "2. Bundesliga - Gruppe S�d";
	static const char* const str_mode_bayernliga = "Bayern-/Landesliga";
#else
	static const char* const str_ini_name = "Ipponboard.ini";
#endif

static const char* const str_golden_score = "Golden Score";
static const char* const str_normal_round_time = "Normal";
static const char* const str_tag_Main = "Main";
static const char* const str_tag_size = "size";
static const char* const str_tag_pos = "pos";
static const char* const str_tag_SecondScreen = "SecondScreen";
static const char* const str_tag_SecondScreenSize = "SecondScreenSize";
static const char* const str_tag_AutoSize = "AutoSize";
static const char* const str_tag_AlwaysShow = "AlwaysShow";
static const char* const str_tag_MatLabel = "MatLabel";
static const char* const str_tag_Language = "Language";
static const char* const str_tag_Version = "Version";
static const char* const str_tag_Fonts = "Fonts";
static const char* const str_tag_TextFont1 = "TextFont1";
static const char* const str_tag_FighterNameFont = "FighterNameFont";
static const char* const str_tag_DigitFont = "DigitFont";
static const char* const str_tag_Colors = "Colors";
static const char* const str_tag_InfoTextColor = "InfoTextColor";
static const char* const str_tag_InfoTextBgColor = "InfoTextBgColor";
static const char* const str_tag_TextColorBlue = "TextColorBlue";
static const char* const str_tag_TextBgColorBlue = "TextBgColorBlue";
static const char* const str_tag_TextColorWhite = "TextColorWhite";
static const char* const str_tag_TextBgColorWhite = "TextBgColorWhite";
static const char* const str_tag_MainClockColorRunning = "MainClockColorRunning";
static const char* const str_tag_MainClockColorStopped = "MainClockColorStopped";
static const char* const str_tag_Styles = "Styles";
static const char* const str_tag_BgStyle = "BackgroundStyle";
static const char* const str_tag_Input = "Input";
static const char* const str_tag_buttonHajimeMate = "ButtonHajimeMate";
static const char* const str_tag_buttonOsaekomiToketa = "ButtonOsaekomiToketa";
static const char* const str_tag_buttonNext = "ButtonNext";
static const char* const str_tag_buttonPrev = "ButtonPrev";
static const char* const str_tag_buttonPause = "ButtonPause";
static const char* const str_tag_buttonReset = "ButtonReset";
static const char* const str_tag_buttonReset2 = "ButtonReset2";
static const char* const str_tag_buttonResetHoldBlue = "ButtonResetHoldBlue";
static const char* const str_tag_buttonResetHoldWhite = "ButtonResetHoldWhite";
static const char* const str_tag_buttonBlueHolding = "ButtonBlueHolding";
static const char* const str_tag_buttonWhiteHolding = "ButtonWhiteHolding";
static const char* const str_tag_buttonHansokumakeBlue = "ButtonHansokumakeBlue";
static const char* const str_tag_buttonHansokumakeWhite = "ButtonHansokumakeWhite";
static const char* const str_tag_invertX = "InvertX";
static const char* const str_tag_invertY = "InvertY";
static const char* const str_tag_invertR = "InvertR";
static const char* const str_tag_invertZ = "InvertZ";
static const char* const str_tag_Sounds = "Sounds";
static const char* const str_tag_sound_time_ends = "TimeEnds";

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	explicit MainWindow( QWidget *parent = 0 );
	virtual ~MainWindow();

protected:
	void changeEvent( QEvent *e );
	void closeEvent( QCloseEvent *event );

private:
	void write_settings();
	void read_settings();
	void update_info_text_color(const QColor& color, const QColor& bgColor);
	void update_text_color_blue(const QColor& color, const QColor& bgColor);
	void update_text_color_white(const QColor& color, const QColor& bgColor);
	void update_fighter_name_font(const QFont&);
	void show_hide_view() const;
	void update_views();
	void change_lang(bool beQuiet = false);
#ifdef TEAM_VIEW
	void update_club_views();
	void UpdateFightNumber_();
	void UpdateScoreScreen_();
	void WriteScoreToHtml_();
#endif

private slots:
#ifdef TEAM_VIEW
	void on_button_current_round_clicked(bool checked);
	void on_comboBox_mode_currentIndexChanged(QString );
	void on_actionSet_Round_Time_triggered();
	void on_pushButton_copySwitched_pressed();
	void on_toolButton_weights_pressed();
#endif
	void on_actionSet_Main_Timer_triggered();
	void on_actionSet_Hold_Timer_triggered();
	void on_action_Info_Header_triggered(bool checked);
	void on_actionLang_English_triggered(bool );
	void on_actionLang_Deutsch_triggered(bool );
	void on_actionContact_Author_triggered();
	void on_actionOnline_Feedback_triggered();
	void on_actionVisit_Project_Homepage_triggered();
	void on_actionAbout_Ipponboard_triggered();
	void on_actionTest_Gong_triggered();
	void on_actionShow_SecondaryView_triggered();
	void on_actionReset_Scores_triggered();
	void on_actionPreferences_triggered();
	void on_button_reset_clicked();
	void EvaluateInput();

#ifdef TEAM_VIEW
	void Print(QPrinter *p)
	{
		QTextEdit e(m_htmlScore, this);
		e.document()->print(p);
	}
	void on_tabWidget_currentChanged(int index);
	void on_actionManage_Clubs_triggered();
	void on_actionLoad_Demo_Data_triggered();
	void on_button_pause_clicked();
	void on_button_prev_clicked();
	void on_button_next_clicked();
	void on_comboBox_club_home_currentIndexChanged(const QString& s);
	void on_comboBox_club_guest_currentIndexChanged(const QString& s);
	void on_actionPrint_triggered();
	void on_actionExport_triggered();
#else
	void on_actionManage_Classes_triggered();
	void on_comboBox_weight_currentIndexChanged(const QString& );
	void on_lineEdit_name_white_textChanged(const QString& );
	void on_lineEdit_name_blue_textChanged(const QString& );
	void on_comboBox_time_currentIndexChanged(const QString& );
	void on_comboBox_weight_class_currentIndexChanged(const QString& );
#endif

private:
	Ui::MainWindow* m_pUi;
	Ipponboard::View* m_pPrimaryView;
	Ipponboard::View* m_pSecondaryView;
	Ipponboard::Controller* m_pController;
#ifdef TEAM_VIEW
	void update_weights(QString weightString);
	Ipponboard::ScoreScreen* m_pScoreScreen;
	Ipponboard::ClubManager* m_pClubManager;
	QString m_htmlScore;
#else
	Ipponboard::FightCategoryMgr* m_pCategoryManager;
#endif
	QString m_MatLabel;
	PGamePad m_pGamePad;

	QFont m_FighterNameFont;
	int m_secondScreenNo;
	bool m_bAlwaysShow;
	bool m_bAutoSize;
	QSize m_secondScreenSize;
	QString m_Language;

	Ipponboard::ControlConfig m_controlCfg;
};

#endif // MAINWINDOW_H
