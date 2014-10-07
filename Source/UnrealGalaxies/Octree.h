#pragma once
#include "Vector.h"
#include "DataNode.h"
#include <vector>

template <class T>
class Octree {
	public:
	Octree(const FVector& _origin, const FVector& _halfSize) : origin(_origin), halfSize(_halfSize), data(NULL) {
		for (int32 i = 0; i < 8; i++) {
			children[i] = NULL;
		}
	}

	~Octree() {
		for (int32 i = 0; i < 8; i++) {
			delete children[i];
		}
		delete data;
	}

	bool IsLeafNode() const {
		return children[0] == NULL;
	}

	int FindOctant(const FVector& point) const {
		int oct = 0;
		if (point.X >= origin.X) oct |= 4;
		if (point.Y >= origin.Y) oct |= 2;
		if (point.Z >= origin.Z) oct |= 1;
		return oct;
	}

	void Insert(const DataNode<T>* node) {
		if (IsLeafNode()) {
			//If leaf and there is no data
			if (data == NULL) {
				data = node;
			}
			//Otherwise split the octree
			else {
				//Save old data
				DataNode<T>* old = data;
				data = NULL;

				//Create octrees and calculate a new bounding-box
				for (int32 i = 0; i < 8; i++) {
					FVector newOrigin = origin;
					newOrigin.X += halfSize.X * (i & 4 ? .5f : -.5f);
					newOrigin.Y += halfSize.Y * (i & 2 ? .5f : -.5f);
					newOrigin.Z += halfSize.Z * (i & 1 ? .5f : -.5f);
					children[i] = new Octree(newOrigin, halfSize * .5f);
				}

				//Now, reinsert the points
				children[FindOctant(old->GetPosition())]->Insert(old);
				children[FindOctant(node->GetPosition())]->Insert(node);
			}
		}
		//Call insert recursivly until we find a leaf
		else {
			children[FindOctant(node->GetPosition())]->Insert(node);
		}
	}

	/*
		Starts a query of the tree for all points inside a defined Bounding-Box
	*/
	void QueryChunk(const FVector& cMin, const FVector& cMax, std::vector<DataNode<T>*>& results) const {
		if (IsLeafNode()) {
			if (data != NULL) {
				FVector& point = data->GetPosition();
				if (point.X > cMax.X || point.Y > cMax.Y || point.Z > cMax.Z) ||
					(point.X < cMin.X || point.Y < cMin.Y || point.Z < cMin.Z) return;
				results.push_back(data);
			}
			else {
				for (int32 i = 0; i < 8; i++) {
					//Get the corners of the bounding box
					FVector max = children[i]->origin + children[i]->halfSize;
					FVector min = children[i]->origin - children[i]->halfSize;

					//Check if this is the correct bounding box
					if !(max.X<cMin.X || max.Y<cMin.Y || max.Z<cMin.Z) ||
						!(min.X>cMax.X || min.Y>cMax.Y || min.Z>cMax.Z) {
							children[i]->QueryChunk(cMin, cMax, results);
					}
				}
			}
		}
	}
	
	private:
	Octree();

	FVector& origin;
	FVector& halfSize;

	Octree* children[8];
	DataNode<T>* data; // If we are a leaf
	
};

