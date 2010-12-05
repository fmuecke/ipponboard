#ifndef FIGHT_CATEGORY_H
#define FIGHT_CATEGORY_H

#include <QString>
#include <QStringList>
#include <vector>
#include <string>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

namespace Ipponboard{

class FightCategory
{
public:
	// Note: class uses std::string instead of QString for
	// better serialization support
	typedef std::vector<std::string> StringList;

	FightCategory()
	{}

	explicit FightCategory( QString const& new_name )
		: name(new_name.toStdString())
		, round_time_secs(0)
		, golden_score_time_secs(0)
		, weights()
	{
	}

	inline bool operator==( std::string const& n ) const
	{
		return name == n;
	}
	inline bool operator==( QString const& n ) const
	{
		return name == n.toStdString();
	}

	const QString ToString() const { return QString::fromStdString(name); }
	const void Rename(QString const& newName) { name.assign(newName.toStdString()); }

	int GetRoundTime() const { return round_time_secs; }
	int GetGoldenScoreTime() const { return golden_score_time_secs; }
	const QString GetRoundTimeStr() const;
	const QString GetGoldenScoreTimeStr() const;
	const QString GetWeights() const { return QString::fromStdString(weights); }
	void SetRoundTime(int secs) { round_time_secs = secs; }
	void SetRoundTime(QString const& str);
	void SetGoldenScoreTime(int secs) { golden_score_time_secs = secs; }
	void SetGoldenScoreTime(QString const& str);
	void SetWeights(QString const& s) { weights.assign(s.toStdString()); }

	QStringList GetWeightsList() const;

private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(name);
		ar & BOOST_SERIALIZATION_NVP(round_time_secs);
		ar & BOOST_SERIALIZATION_NVP(golden_score_time_secs);
		ar & BOOST_SERIALIZATION_NVP(weights);
	}

	std::string name;
	int round_time_secs;
	int golden_score_time_secs;
	std::string weights;
};

typedef std::vector<FightCategory> FightCategoryList;

} // namespace Ipponboard

#endif // FIGHT_CATEGORY_H
