#include <string>
#include <vector>
#include "Edge.h"

struct Coordinate{
    double mLatitude;
    double mLongitude;

    Coordinate()
    {
        mLatitude = 0;
        mLongitude = 0;
    }

    Coordinate(double pLatitude, double pLongitude)
    {
        mLatitude = pLatitude;
        mLongitude = pLongitude;
    }
};


class Node{
private:
    // Name of the node
    std::string mName;

    // Adjacency list
    std::vector<Edge*> mAdjacencyList;

    // total cost, up to this node
    double mCost;

    // previous node (to store path information)
    Node* mPrev;

    // coordinate of each node
    Coordinate* mCoord;

    double mG;
    double mH;
    double mF;
public:
    // Constructors
    Node();
    Node(const std::string& pName, Coordinate* pCoordinate);


    // Getters
    std::string getName();
    std::vector<Edge*> getAdjacencyList();
    Node* getPrev();
    double getCost();
    Coordinate* getCoord();
    double getG();
    double getH();
    double getF();

    // Setters
    void setName(std::string& pName);
    void addAdjacencyList(Edge* pEdge);
    void setPrev(Node* pNode);
    void setCost(double pCost);
    void setCoord(Coordinate* pCoord);
    void setG(double pG);
    void setH(double pH);
    void setF(double pF);
};
