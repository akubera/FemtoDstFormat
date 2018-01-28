#ifndef FEMTO_EVENT_H
#define FEMTO_EVENT_H

#include "FemtoDstBranch.h"

class FemtoEvent : public FemtoDstBranch
{
public:
	virtual const char* classname() const { return "FemtoEvent"; }
	FemtoEvent() {
		mPrimaryVertex_mX1 = 0.0;
		mPrimaryVertex_mX2 = 0.0;
		mPrimaryVertex_mX3 = 0.0;
		mWeight            = 0.0;
		mRunId             = 0;
		mEventId           = 0;
		mTriggerWord       = 0;
		mTriggerWordMtd    = 0;
		mGRefMult          = 0;
		mPsi2              = 0;
		mBin16             = 0;
		mRunIndex          = 0;
	}

	virtual ~FemtoEvent() {}

	FemtoEvent& operator=(const FemtoEvent& rhs) {
		if (this == &rhs) {
			return *this;
		}
		FemtoDstBranch::operator=(rhs);

		mPrimaryVertex_mX1 = rhs.mPrimaryVertex_mX1;
		mPrimaryVertex_mX2 = rhs.mPrimaryVertex_mX2;
		mPrimaryVertex_mX3 = rhs.mPrimaryVertex_mX3;
		mWeight            = rhs.mWeight;
		mRunId             = rhs.mRunId;
		mEventId           = rhs.mEventId;
		mPsi2              = rhs.mPsi2;
		mTriggerWord       = rhs.mTriggerWord;
		mTriggerWordMtd    = rhs.mTriggerWordMtd;
		mGRefMult          = rhs.mGRefMult;
		mBin16             = rhs.mBin16;
		mRunIndex          = rhs.mRunIndex;

		return *this;
	}

	void copy( FemtoEvent * that ){
		*this = *that;
	}

	float psi() { return mPsi2 / 10000.0; }

	int year() const { return (mRunId / 1000000) - 1 + 2000; }

	void vertex( Float_t x, Float_t y, Float_t z ){
		this->mPrimaryVertex_mX1 = x;
		this->mPrimaryVertex_mX2 = y;
		this->mPrimaryVertex_mX3 = z;
	}

	template <typename T>
	T v( std::string name ){
		if ( name == "mPrimaryVertex_mX1" ) return mPrimaryVertex_mX1;
		if ( name == "mPrimaryVertex_mX2" ) return mPrimaryVertex_mX2;
		if ( name == "mPrimaryVertex_mX3" ) return mPrimaryVertex_mX3;
		if ( name == "mWeight" ) return mWeight;
		if ( name == "mRunId" ) return mRunId;
		if ( name == "mEventId" ) return mEventId;
		if ( name == "mTriggerWord" ) return mTriggerWord;
		if ( name == "mTriggerWordMtd" ) return mTriggerWordMtd;
		if ( name == "mGRefMult" ) return mGRefMult;
		if ( name == "mPsi2" ) return mPsi2;
		if ( name == "mBin16" ) return mBin16;
		if ( name == "mRunIndex" ) return mRunIndex;
		return 0;
	}


	Float_t 	mPrimaryVertex_mX1;		// Event VertexX
	Float_t 	mPrimaryVertex_mX2;		// Event VertexY
	Float_t 	mPrimaryVertex_mX3;		// Event VertexZ
	Float_t 	mWeight;				// Event weight from StRefMultCorr
	Int_t 		mRunId;					// Run ID
	Int_t 		mEventId;				// Event Id
	UInt_t 		mTriggerWord;			// Trigger word
	UInt_t 		mTriggerWordMtd;		// MTD trigger word
	UShort_t 	mGRefMult;				// global RefMult
	Short_t 	mPsi2;					// event plane angle * 10000
	UChar_t 	mBin16;					// centrality bin 16
	UShort_t 	mRunIndex;				// the run index

	virtual bool isDiMuon() const {
		if(year()==2014){
			for(Int_t i=0; i<8; i++) {
				if(mTriggerWordMtd & (1<<i)) return true;
			}
		} else if(year()==2013) {
			for(Int_t i=0; i<2; i++) {
				if(mTriggerWordMtd & (1<<i)) return true;
			}
		} else if(year()==2015){
			for(Int_t i=0; i<5; i++) {
				if(mTriggerWordMtd & (1<<i))
					return kTRUE;
			}
		}
		return false;
	}

	virtual bool isDiMuonHFT() const {
		if(year()==2014){
			for(Int_t i=5; i<8; i++){
				if(mTriggerWordMtd & (1<<i)) return true;
			}
		}
		return false;
	}

	virtual bool isSingleMuon() const {
		if(year()==2014){
			for(Int_t i=13; i<18; i++){
				if(mTriggerWordMtd & (1<<i)) return true;
			}
		} else if(year()==2013) {
			for(Int_t i=5; i<7; i++) {
				if(mTriggerWordMtd & (1<<i)) return true;
			}
		} else if(year()==2015) {
			for(Int_t i=10; i<15; i++) {
				if(mTriggerWordMtd & (1<<i))
					return kTRUE;
			}
		}
		return false;
	}

	virtual bool isEMuon() const {
		if(year()==2014){
			for(Int_t i=8; i<13; i++) {
				if(mTriggerWordMtd & (1<<i)) return true;
			}
		} else if(year()==2013) {
			for(Int_t i=2; i<5; i++) {
				if(mTriggerWordMtd & (1<<i)) return true;
			}
		} else if( year()==2015) {
			for(Int_t i=5; i<10; i++) {
				if(mTriggerWordMtd & (1<<i))
					return kTRUE;
			}
		}
		return false;
	}

	virtual bool isMtdTrigger( std::string trigger ){
		if ( "all" == trigger )
			return true;
		if ( "dimuon" == trigger || "DiMuon" == trigger || "DIMUON" == trigger || "Dimuon" == trigger )
			return isDiMuon();
		if ( "singlemuon" == trigger || "SINGLEMUON" == trigger || "SingleMuon" == trigger || "singlemu" == trigger )
			return isSingleMuon();
		if ( "dimuonhft" == trigger )
			return isDiMuonHFT();
		if ( "emu" == trigger )
			return isEMuon();
		return false;
	}


	ClassDef( FemtoEvent, 3 )
};


#endif
