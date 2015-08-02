#include "EngaugeAssert.h"
#include "FormatCoordsUnitsNonPolarTheta.h"
#include "FormatDateTime.h"
#include "FormatDegreesMinutesSecondsNonPolarTheta.h"
#include "Logger.h"

FormatCoordsUnitsNonPolarTheta::FormatCoordsUnitsNonPolarTheta ()
{
}

double FormatCoordsUnitsNonPolarTheta::formattedToUnformatted (const QString &string,
                                                               CoordUnitsNonPolarTheta coordUnits,
                                                               CoordUnitsDate coordUnitsDate,
                                                               CoordUnitsTime coordUnitsTime) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatCoordsUnitsNonPolarTheta::formattedToUnformatted";

  double value;

  switch (coordUnits) {
    case COORD_UNITS_NON_POLAR_THETA_DATE_TIME:
      {
        FormatDateTime format;
        ENGAUGE_ASSERT (format.parseInput (coordUnitsDate,
                                           coordUnitsTime,
                                           string,
                                           value) == QValidator::Acceptable);
      }
      break;

    case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS:
    case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
      {
        FormatDegreesMinutesSecondsNonPolarTheta format;
        ENGAUGE_ASSERT (format.parseInput (string,
                                           value) == QValidator::Acceptable);
      }
      break;

    case COORD_UNITS_NON_POLAR_THETA_NUMBER:
      value = string.toDouble ();
      break;

    default:
      LOG4CPP_ERROR_S ((*mainCat)) << "FormatCoordsUnitsNonPolarTheta::formattedToFormatted";
      ENGAUGE_ASSERT (false);
      break;
  }

  return value;
}

QString FormatCoordsUnitsNonPolarTheta::unformattedToFormatted (double valueUnformatted,
                                                                CoordUnitsNonPolarTheta coordUnits,
                                                                CoordUnitsDate coordUnitsDate,
                                                                CoordUnitsTime coordUnitsTime,
                                                                bool isXTheta,
                                                                int precisionDigitsForRawNumber) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "FormatCoordsUnitsNonPolarTheta::unformattedToFormatted";

  const char FORMAT ('g');

  QString valueFormatted;

  switch (coordUnits) {
    case COORD_UNITS_NON_POLAR_THETA_DATE_TIME:
      {
        FormatDateTime format;
        valueFormatted = format.formatOutput (coordUnitsDate,
                                              coordUnitsTime,
                                              valueUnformatted);
      }
      break;

    case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS:
    case COORD_UNITS_NON_POLAR_THETA_DEGREES_MINUTES_SECONDS_NSEW:
      {
        FormatDegreesMinutesSecondsNonPolarTheta format;
        valueFormatted = format.formatOutput (coordUnits,
                                              valueUnformatted,
                                              isXTheta);
      }
      break;

    case COORD_UNITS_NON_POLAR_THETA_NUMBER:
      valueFormatted = QString::number (valueUnformatted,
                                        FORMAT,
                                        precisionDigitsForRawNumber);
      break;

    default:
      LOG4CPP_ERROR_S ((*mainCat)) << "FormatCoordsUnitsNonPolarTheta::unformattedToFormatted";
      ENGAUGE_ASSERT (false);
      break;
  }

  return valueFormatted;
}
