#pragma once
#include "GG_Gear3D.h"

namespace GenerativeGeometry {
	 
	class Chain {
		VEC<Gear3D*> Gear3D_Chain = {};
	public:
		Chain() {};
		int GetChainLength() const { return Gear3D_Chain.size(); };
		void AddGear3D(Gear3D* gearPointer)  {
			if (!Gear3D_Chain.empty()) {
				auto prevRotFactor = Gear3D_Chain[Gear3D_Chain.size() - 1]->GetRotFactor();
				gearPointer->SetRotFactor(-prevRotFactor);
			}
			Gear3D_Chain.push_back(gearPointer);
		};
	};
};