#include <airmap/date_time.h>

namespace {
constexpr const char* format{"%Y-%m-%dT%H:%M:%sZ"};
}  // namespace

std::uint64_t airmap::milliseconds_since_epoch(const DateTime& dt) {
  static const DateTime epoch = boost::posix_time::time_from_string("1970-01-01 00:00:00.000");
  return (dt - epoch).total_milliseconds();
}

airmap::DateTime airmap::iso8601::parse(const std::string& s) {
  boost::posix_time::time_input_facet facet{format, 1};

  std::istringstream iss{s};
  iss.imbue(std::locale{iss.getloc(), &facet});
  DateTime result;
  iss >> result;

  return result;
}

std::string airmap::iso8601::generate(const DateTime& dt) {
  boost::posix_time::time_facet facet(1);
  facet.format(format);

  std::ostringstream oss;
  oss.imbue(std::locale(oss.getloc(), &facet));

  oss << dt;

  return oss.str();
}