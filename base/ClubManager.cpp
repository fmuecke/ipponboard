#include "ClubManager.h"
#include <QMessageBox>

#include <iostream>
#include <fstream>
#include "../util/qstring_serialization.h"
#include "../util/path_helpers.h"
#include <boost/serialization/vector.hpp>
#include <algorithm>


using namespace Ipponboard;
const char* const ClubManager::str_filename_club_definitions = "clubs\\clubs.xml";

//---------------------------------------------------------
ClubManager::ClubManager()
	: m_Clubs()
//---------------------------------------------------------
{
	LoadClubs_();
	SortClubs();
}

//---------------------------------------------------------
ClubManager::~ClubManager()
//---------------------------------------------------------
{
	SaveClubs_();
}

//---------------------------------------------------------
bool ClubManager::GetClub(int index, Ipponboard::Club& club) const
//---------------------------------------------------------
{
	try
	{
		club = m_Clubs.at(index);
	}
	catch (std::out_of_range&)
	{
		return false;
	}

	return true;
}

//---------------------------------------------------------
QString ClubManager::GetLogo(const QString& clubName) const
//---------------------------------------------------------
{
	for (unsigned i(0); i < m_Clubs.size(); ++i)
	{
		if (clubName == m_Clubs.at(i).name)
			return m_Clubs.at(i).logoFile;
	}

	return QString();
}

//---------------------------------------------------------
QString ClubManager::GetAddress(const QString& clubName) const
//---------------------------------------------------------
{
	for (unsigned i(0); i < m_Clubs.size(); ++i)
	{
		if (clubName == m_Clubs.at(i).name)
			return m_Clubs.at(i).address;
	}

	return QString();
}

//---------------------------------------------------------
void ClubManager::AddClub(const Ipponboard::Club& club)
//---------------------------------------------------------
{
	m_Clubs.push_back(club);
}

//---------------------------------------------------------
void ClubManager::UpdateClub(unsigned int index, const Ipponboard::Club& club)
//---------------------------------------------------------
{
	m_Clubs.at(index) = club;
}

//---------------------------------------------------------
void ClubManager::RemoveClub(unsigned int index)
//---------------------------------------------------------
{
	Q_ASSERT(index < m_Clubs.size() && index >= 0);

	m_Clubs.erase(m_Clubs.begin() + index);
}

//---------------------------------------------------------
void ClubManager::SortClubs()
//---------------------------------------------------------
{
	std::sort(m_Clubs.begin(), m_Clubs.end());
}

//---------------------------------------------------------
void ClubManager::LoadClubs_()
//---------------------------------------------------------
{
	// open the archive

	//m_Clubs.push_back(Club("TSV K�nigsbrunn", "..\\base\\emblems\\koenigsbrunn.png"));
	//m_Clubs.push_back(Club("TV Lenggries", "..\\base\\emblems\\tv_lenggries.png"));

	const std::string filePath(
		fmu::GetSettingsFilePath(str_filename_club_definitions));

	std::ifstream ifs(filePath.c_str());

	if (ifs.good())
	{
		try
		{
			boost::archive::xml_iarchive ia(ifs);
			// restore the clubs from the xml archive
			ia >> BOOST_SERIALIZATION_NVP(m_Clubs);
		}
		catch (std::exception&)
		{
			QMessageBox::critical(0, QString("Error"),
								  QString("Unable to parse %1!").arg(
									  str_filename_club_definitions));
		}
	}
	else
	{
		QMessageBox::critical(0, QString("Error"),
							  QString("Unable to open %1!").arg(
								  str_filename_club_definitions));

	}

	ifs.close();
}

//---------------------------------------------------------
void ClubManager::SaveClubs_()
//---------------------------------------------------------
{
	// make an archive
	const std::string filePath(
		fmu::GetSettingsFilePath(str_filename_club_definitions));

	std::ofstream ofs(filePath.c_str());

	if (ofs.good())
	{
		boost::archive::xml_oarchive oa(ofs);
		oa << BOOST_SERIALIZATION_NVP(m_Clubs);
	}
	else
	{
		QMessageBox::critical(0, QString("Error"),
							  QString("Unable to save %1!").arg(
								  str_filename_club_definitions));
	}

	ofs.close();
}