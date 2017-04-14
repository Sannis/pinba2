#ifndef PINBA__MYSQL_ENGINE__VIEW_CONF_H_
#define PINBA__MYSQL_ENGINE__VIEW_CONF_H_

#include <memory>
#include <string>
#include <vector>

#include <meow/smart_enum.hpp>

#include "pinba/globals.h"

////////////////////////////////////////////////////////////////////////////////////////////////

MEOW_DEFINE_SMART_ENUM_STRUCT(pinba_view_kind,
								((stats,                   "stats"))
								((active_reports,          "active_reports"))
								((report_by_request_data,  "report_by_request_data"))
								((report_by_timer_data,    "report_by_timer_data"))
								((report_by_packet_data,   "report_by_packet_data"))
								);

struct pinba_view_conf_t
{
	std::string                 orig_comment;

	std::string                 name;
	pinba_view_kind_t           kind;
	duration_t                  time_window;
	uint32_t                    tick_count;

	std::vector<str_ref>        keys;

	struct filter_spec_t
	{
		str_ref key;
		str_ref value;
	};
	std::vector<filter_spec_t>  filters;

	uint32_t                    hv_bucket_count;
	duration_t                  hv_bucket_d;
	std::vector<double>         percentiles;

	duration_t                  min_time;    // 0 if unset
	duration_t                  max_time;    // 0 if unset
};
using pinba_view_conf_ptr = std::unique_ptr<pinba_view_conf_t>;

////////////////////////////////////////////////////////////////////////////////////////////////

struct report_conf___by_packet_t;
struct report_conf___by_request_t;
struct report_conf___by_timer_t;

report_conf___by_packet_t const*   pinba_view_conf_get___by_packet(pinba_view_conf_t const&);
report_conf___by_request_t const*  pinba_view_conf_get___by_request(pinba_view_conf_t const&);
report_conf___by_timer_t const*    pinba_view_conf_get___by_timer(pinba_view_conf_t const&);

pinba_view_conf_ptr pinba_view_conf_parse(str_ref table_name, str_ref conf_string);

////////////////////////////////////////////////////////////////////////////////////////////////

#endif // PINBA__MYSQL_ENGINE__VIEW_CONF_H_