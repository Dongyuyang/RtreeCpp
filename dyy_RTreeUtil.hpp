#ifndef _DYY_RTREEUTIL_HPP_
#define _DYY_RTREEUTIL_HPP_

#include "dyy_data.hpp"
#include <cmath>

namespace dyy{

/*********************************************************************
 * Point + dis Entry
 ********************************************************************/

class PDEntry
{
public:
    Node_P nodePtr;
    double dis;

    PDEntry(Node_P _nodePtr, double _dis) : nodePtr(_nodePtr), dis(_dis){};

    struct ascending : public std::binary_function<PDEntry , PDEntry, bool>
    {
        bool operator()(const PDEntry &_a, const PDEntry &_b) const
        {return _a.dis < _b.dis;}
    };

};
/*********************************************************************
 *  ARank result
 ********************************************************************/

class ARankResult
{
public:
    bool isBetter;
    int rank;

    /*
                1:All in
      flag =    0:Need check children
               -1:All out
    */
    int flag;
};



/*********************************************************************
 * RStarTreeUtil
 ********************************************************************/

class RStarTreeUtil
{
public:
    RStarTreeUtil(){}

    /*Nearest neighbor query*/
    static Point NNquery(RStarTree &tree, Point &point);

    /*ARank*/
    static ARankResult ARank(RStarTree &tree, Point &w, int minRank,
                             Point &Qlow, Point &Qup, Point_V &Q);

    static ARankResult ARankPW(RStarTree &tree, Mbr &Ew, int minRank,
                               Point &Qlow, Point &Qup, Point_V &Q);

    static ARankResult CARank(RStarTree &tree, Point &w, int minRank,
                              std::vector<Point_V> &QC,
                              std::vector<Mbr> &QCMbr);

    //inline functions
    //Euclid distance
    static double minDis2(Point &point, Mbr &mbr);
    static double maxDis2(Point &point, Mbr &mbr);
    static double dis2(Point &point, Mbr &mbr);

    //Inner product
    static double dot(Point &a, Point &b);
    static double dotMbrLow(Point &point, Mbr &mbr);
    static double dotMbrUp(Point &point, Mbr &mbr);
    static double dotMMLow(Mbr &a, Mbr &b);
    static double dotMMUp(Mbr &a, Mbr &b);

};

inline double RStarTreeUtil::dot(Point &a, Point &b)
{
    double score = 0;
    for(size_t dim = 0; dim < DIM; dim++)
        score += a.coords[dim] * b.coords[dim];
    return score;
}

inline double RStarTreeUtil::dotMbrLow(Point &point, Mbr &mbr)
{
    double score = 0;
    for(size_t dim = 0; dim < DIM; dim++)
        score += point.coords[dim] * mbr.coord[dim][0];
    return score;
}

inline double RStarTreeUtil::dotMbrUp(Point &point, Mbr &mbr)
{
    double score = 0;
    for(size_t dim = 0; dim < DIM; dim++)
        score += point.coords[dim] * mbr.coord[dim][1];
    return score;
}

inline double RStarTreeUtil::dotMMLow(Mbr &a, Mbr &b)
{
    double score = 0;
    for(size_t dim = 0; dim < DIM; dim++)
        score += a.coord[dim][0] * b.coord[dim][0];
    return score;
}

inline double RStarTreeUtil::dotMMUp(Mbr &a, Mbr &b)
{
    double score = 0;
    for(size_t dim = 0; dim < DIM; dim++)
        score += a.coord[dim][1] * b.coord[dim][1];
    return score;
}

inline double RStarTreeUtil::minDis2(Point &point, Mbr &mbr)
{
    double dis = 0;
    for(size_t dim = 0; dim < DIM; dim++){
        if(mbr.coord[dim][0] > point.coords[dim] ||
           mbr.coord[dim][1] < point.coords[dim])
            {
                double diff =
                    std::min(std::abs(mbr.coord[dim][0] - point.coords[dim]),
                             std::abs(mbr.coord[dim][1] - point.coords[dim])
                             );
                dis += diff * diff;
            }
    }
    return dis;
}

inline double RStarTreeUtil::maxDis2(Point &point, Mbr &mbr)
{
    double dis = 0;
    for(size_t dim = 0; dim < DIM; dim++){
        double diff =
            std::max(std::abs(mbr.coord[dim][0] - point.coords[dim]),
                     std::abs(mbr.coord[dim][1] - point.coords[dim]));
        dis += diff * diff;
    }
    return dis;
}

inline double RStarTreeUtil::dis2(Point &point, Mbr &mbr)
{
    double dis = 0;
    for(size_t dim = 0; dim < DIM; dim++){
        double diff = mbr.coord[dim][0] - point.coords[dim];
        dis += diff * diff;
    }
    return dis;
}

}






#endif /*_DYY_RTREEUTIL_HPP_*/
