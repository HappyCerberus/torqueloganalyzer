#ifndef DATA_H
#define DATA_H

// STD C++
#include <vector>
#include <string>
#include <set>
#include <map>

// BOOST
#include <boost/optional/optional_io.hpp>
#include <boost/fusion/adapted/struct.hpp>

struct JobData
{
  std::string timestamp;
  char event;
  std::string id;
  struct Fields {
    boost::optional<int64_t> time_arriv;
    boost::optional<int64_t> time_start;
    boost::optional<int64_t> time_compl;
    boost::optional<int64_t> time_eligb;
    boost::optional<std::string> queue;
    boost::optional<std::string> owner;
    boost::optional<int> resc_total_cores;
    boost::optional<std::string> resc_total_mem;
    boost::optional<std::string> req_walltime;
    boost::optional<std::string> exec_host;
    boost::optional<std::string> nodespec;

    Fields() : time_arriv(), time_start(), time_compl(), time_eligb(), queue() {}
  } fields;

  JobData() : timestamp(), event(), id(), fields() {}
};

BOOST_FUSION_ADAPT_STRUCT(JobData::Fields,
	(boost::optional<int64_t>, time_arriv)
	(boost::optional<int64_t>, time_start)
	(boost::optional<int64_t>, time_compl)
	(boost::optional<int64_t>, time_eligb)
	(boost::optional<std::string>, queue)
	(boost::optional<std::string>, owner)
	(boost::optional<int>, resc_total_cores)
	(boost::optional<std::string>, resc_total_mem)
	(boost::optional<std::string>, req_walltime)
	(boost::optional<std::string>, exec_host)
	(boost::optional<std::string>, nodespec)
    )

BOOST_FUSION_ADAPT_STRUCT(JobData,
	(std::string, timestamp)
	(char, event)
	(std::string, id)
  (JobData::Fields, fields)
    )

struct FullJob
{
    JobData* event_arrive;
    JobData* event_start;
    JobData* event_compl;

    FullJob() : event_arrive(NULL), event_start(NULL), event_compl(NULL) {}
};

extern std::vector<JobData> data;
extern std::set<std::string> users;
extern std::map<std::string, FullJob> full_data;
extern std::set<std::string> job_blacklist;
extern std::map< std::string,std::vector<JobData*> > data_by_user;

void callback(const char * const begin, const char * const end);
void finish_processing();
void construct_fulljob_information();
bool validate_job(std::string jobid);

#endif // DATA_H
