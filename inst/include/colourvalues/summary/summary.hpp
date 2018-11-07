#ifndef COLOURVALUES_SUMMARY_H
#define COLOURVALUES_SUMMARY_H

#include <Rcpp.h>

namespace colourvalues {
namespace summary {

  /*
   * Returns evenly spaced values from a vector
   * The idea is to use the same palette as the vector to then get the values and colours
   * to use in a legend
   */
  inline Rcpp::NumericVector numeric_summary( Rcpp::NumericVector& nv, std::size_t n ) {

    size_t n_summaries = n < nv.length() ? n : nv.length();

    if ( n_summaries == 1 ) {
      return nv;
    }

    Rcpp::NumericVector vals( n_summaries );

    double x = Rcpp::min( nv );
    double y = Rcpp::max( nv );
    double h = ( y - x ) / static_cast< double >( n_summaries - 1 );
    Rcpp::NumericVector::iterator it;
    double val;
    for ( it = vals.begin(), val = x; it != vals.end(); it++, val += h ) {
      *it = val;
    }
    return vals;
  }


} // namespace summary
} // namespace colourvalues

#endif
