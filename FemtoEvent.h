#ifndef FEMTO_EVENT_H
#define FEMTO_EVENT_H

#include "FemtoDstBranch.h"
#include <algorithm>

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

		switch (year()) {
		case 2014:
			return mTriggerWordMtd & 0xFF; // first 8 bits
		case 2013:
			return mTriggerWordMtd & 0x03; // first 2 bits
		case 2015:
			return mTriggerWordMtd & 0x1F; // first 5 bits [0,4]
		}
		return false;
	}

	virtual bool isDiMuonHFT() const {
		switch (year()) {
		case 2014:
			return mTriggerWordMtd & 0xE0; // bits [5,8)
		}
		return false;
	}

	virtual bool isSingleMuon() const {
		switch (year()) {
		case 2014:
			return mTriggerWordMtd & 0x3E000; // bits [13,18)
		case 2013:
			return mTriggerWordMtd & 0x00060; // bits [5,7)
		case 2015:
			return mTriggerWordMtd & 0x07C00; // bits [10,15)
		}
		return false;
	}

	virtual bool isEMuon() const {
		switch (year()) {
		case 2014:
			return mTriggerWordMtd & 0x1F00; // bits [8,13)
		case 2013:
			return mTriggerWordMtd & 0x001C; // bits [2, 5)
		case 2015:
			return mTriggerWordMtd & 0x03E0; // bits [5, 10)
		}
		return false;
	}

	virtual bool isMtdTrigger( std::string trigger ){
                // make trigger lowercase
		std::transform(trigger.begin(), trigger.end(), trigger.begin(), ::tolower);

		if ( "all" == trigger )
			return true;
		else if ( "dimuon" == trigger)
			return isDiMuon();
		else if ( "singlemuon" == trigger)
			return isSingleMuon();
		else if ( "dimuonhft" == trigger )
			return isDiMuonHFT();
		else if ( "emu" == trigger )
			return isEMuon();

		return false;
	}


	ClassDef( FemtoEvent, 3 )
};


#endif
