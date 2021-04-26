#pragma once
#include "Const.h"

class LopTC{
private:
	int maLopTC;
	string maMH;
	int nienKhoa;
	int hocKy;
	int nhom;
	int svMax;
	int svMin;
	bool huyLop;
	int soSVDK;
	DSDK dsdk;
public:
	LopTC();
	~LopTC();
	
	void setMaLopTC(int maLopTC);
	void setMaMH(string maMH);
	void setNienKhoa(int khoa);
	void setHocKy(int hocKy);
	void setNhom(int nhom);
	void setSVMax(int svMax);
	void setSVMin(int svMin);
	void setTrangThai(bool huyLop);
	void setDSDK(DSDK DS);
	
	int getMaLopTC();
	string getMaMH();
	int getNienKhoa();
	int getHocKy();
	int getNhom();
	int getSVMax();
	int getSVMin();
	bool getTrangThai();
	DSDK &getDSDK();
	
	int getSoSVDK(){
		return this->soSVDK;
	}
	
	void setSoSVDK(int soSVDK){
		this->soSVDK = soSVDK;
	}
	
	void taoMaLop_LTC(int nLTC)	{
			this->maLopTC = nLTC +1;
		}
	
	void nhap_LTC(){
		cin.ignore();
		cout<<"\nNhap ma mh ";
		getline(cin,maMH);
		cout<<"\nNhap nien khoa: ";
		cin>>nienKhoa;
		cout<<"\nNhap hoc ky: ";
		cin>>hocKy;
		cout<<"\nNhap nhom: ";
		cin>>nhom;
		cout<<"\nNhap so sv max: ";
		cin>>svMax;
		cout<<"\nNhap so sv min: ";
		cin>>svMin;
		
	}
	
	
	void xuat_LTC(){
		cout<<"\nMa lop TC: "<<maLopTC;
		cout<<"\nMa mh: "<<maMH;
		cout<<"\nkhoa: "<<nienKhoa;
		cout<<"\nHoc ky: "<<hocKy;
		cout<<"\nNhom: "<<nhom;
		cout<<"\nsvMax: "<<svMax;
		cout<<"\nsvMin: "<<svMin;
		if(huyLop) cout<<"\nHuy lop: true";
		else cout<<"\nHuy lop: false";
		if(dsdk.getHead_DSDK() == NULL) cout<<"\ndk null";
		else cout<<"\ndsk not null";
	}
	
	bool checkTrung_LTC(LopTC ltc){
		
		if(this->maMH == ltc.maMH && this->nienKhoa == ltc.nienKhoa && this->hocKy == ltc.hocKy && this->nhom == ltc.nhom)
			return true;
			
		return false;
	}
};

class DSLopTC{
private:
	LopTC *lopTC[MAX_LOPTC] = {NULL};
	int n;	
public:
	
	DSLopTC();
	~DSLopTC();
	int getN();
	
	bool isNull_LTC();
	bool isFull_LTC();
	

	int them_LTC(LopTC *LTC);
	int xoa_LTC(int maLopTC);
	int tim_LTC(int maLopTC);
	
	void writeData_LTC(LopTC *LTC, ofstream &fileOut);
	void writeDataDS_LTC();
	
	void loadDataDS_LTC(){
		ifstream fileIn; char temp;
		fileIn.open("data\\DSLTC.txt", ios::in);
		int tempInt; string tempStr;
		while (!fileIn.eof())
		{
			
			lopTC[n] = new LopTC;
			fileIn >> tempInt;	lopTC[n]->setMaLopTC(tempInt);
			fileIn >> temp;
			getline(fileIn, tempStr, ','); lopTC[n]->setMaMH(tempStr);
			fileIn >> tempInt; lopTC[n]->setNienKhoa(tempInt);
			fileIn >> temp;
			fileIn >> tempInt; lopTC[n]->setHocKy(tempInt);
			fileIn >> temp;
			fileIn >> tempInt; lopTC[n]->setNhom(tempInt);
			fileIn >> temp;
			fileIn >> tempInt; lopTC[n]->setSVMax(tempInt);
			fileIn >> temp;
			fileIn >> tempInt; lopTC[n]->setSVMin(tempInt);
			fileIn >> temp;
			fileIn >> tempInt; lopTC[n]->setTrangThai(bool(tempInt));
			
	
			lopTC[n]->getDSDK().setHead_DSDK(NULL);
			
	
			this->n++;
	
			if (fileIn.eof()) break;
		}
		fileIn.close();
	}
	
	void xuatDS_LTC(){
		if(n==0) cout<<"\nDS ltc rong";
		for(int i=0; i<n; i++){
			cout<<"\n";
			lopTC[i]->xuat_LTC();
		}
	}
	
	int sua_LTC(int maLopTC){
		int viTri = tim_LTC( maLopTC);
		if (viTri >= 0)	{
			
			this->lopTC[viTri]->nhap_LTC();
			return 1;
		}
		
		return -1;
	}
	
	bool checkDK_LTC(int viTri, string maSV){
		
		if(this->lopTC[viTri]!= NULL){
			if(this->lopTC[viTri]->getDSDK().checkSV_DK(maSV)) return true;
		}
		
		return false;
	}
	
	void DK_LTC(int viTri, NodeDK *DK){
		if(this->lopTC[viTri]!= NULL){
			this->lopTC[viTri]->getDSDK().them_DK(DK);
			cout<<"\n Dk thanh cong";
			this->lopTC[viTri]->setSoSVDK(this->lopTC[viTri]->getSoSVDK() + 1);
		}
	}
	
	void xuatDSDK_LTC(int viTri){
		if(this->lopTC[viTri]!= NULL){
			this->lopTC[viTri]->getDSDK().xuatDS_DK();
			
		}
	}
	
	bool checkTrungDS_LTC(LopTC *ltc){
		if(this->isNull_LTC()) return false;
		
		for(int i=0; i<n; i++){
			if(this->lopTC[i]->checkTrung_LTC(*(ltc))) return true;
		}
		
		return false;
	}
	
};

/*
** ================ LopTC ================
*/

LopTC::LopTC(){
	maLopTC = 0;
	maMH = "";
	nienKhoa = 2021;
	hocKy = 0;
	nhom = 0;
	svMax = 0;
	svMin = 0;
	huyLop = false;
	soSVDK = 0;
	dsdk.setHead_DSDK(NULL);
}

LopTC::~LopTC(){
	
}

void LopTC::setMaLopTC(int maLopTC){
	this->maLopTC = maLopTC;	
}

void LopTC::setMaMH(string maMH){
	this->maMH = maMH;
}

void LopTC::setNienKhoa(int khoa){
	this->nienKhoa = khoa;
}

void LopTC::setHocKy(int hocKy){
	this->hocKy = hocKy;
}

void LopTC::setNhom(int nhom){
	this->nhom = nhom;
}

void LopTC::setSVMax(int svMax){
	this->svMax = svMax;
}

void LopTC::setSVMin(int svMin){
	this->svMin = svMin;
}

void LopTC::setTrangThai(bool huyLop){
	this->huyLop = huyLop;
}
void LopTC::setDSDK(DSDK DS){
	this->dsdk = DS; 
}
	
int LopTC::getMaLopTC(){
	return this->maLopTC;	
}

string LopTC::getMaMH(){
	return this->maMH;
}

int LopTC::getNienKhoa(){
	return this->nienKhoa;
}

int LopTC::getHocKy(){
	return this->hocKy;
}

int LopTC::getNhom(){
	return this->nhom;
}

int LopTC::getSVMax(){
	return this->svMax;
}

int LopTC::getSVMin(){
	return this->svMin;
}

bool LopTC::getTrangThai(){
	return this->huyLop;
}

DSDK &LopTC::getDSDK(){
	return this->dsdk;
}



/*
** ================ Danh sach LopTC ================
*/

DSLopTC::DSLopTC(){
	n = 0;
	//for(int i=0; i<MAX_LOPTC; i++) lopTC[i] = NULL;
	
}

DSLopTC::~DSLopTC(){
	for(int i=0; i<n; i++)
		delete this->lopTC[i];
}

int DSLopTC::getN(){
	return this->n;
}

bool DSLopTC::isNull_LTC(){
	return this->n == 0;
}

bool DSLopTC::isFull_LTC(){
	return this->n >= MAX_LOPTC;
}

int DSLopTC::tim_LTC(int maLopTC){
	for(int i=0; i<this->n; i++)
		if(this->lopTC[i]->getMaLopTC() == maLopTC)
			return i;
	return -1;
}

int DSLopTC::them_LTC(LopTC *LTC){
	if(isFull_LTC()) return 0;
	
	this->lopTC[this->n++] = LTC;
	return 1;
}

int DSLopTC::xoa_LTC(int maLopTC){
	
	int viTri = tim_LTC(maLopTC);
	if(viTri>=0){
		
		delete this->lopTC[viTri];
		
		for (int i = viTri; i < this->n; i++)
			this->lopTC[i] = this->lopTC[i + 1];

		this->n--;
		
		return 1;
	}
	
	return -1;
	
}



void DSLopTC::writeData_LTC(LopTC *LTC, ofstream &fileOut){
	char temp = ',';
	fileOut << LTC->getMaLopTC();
	fileOut << temp;
	fileOut << LTC->getMaMH();
	fileOut << temp;
	fileOut << LTC->getNienKhoa();
	fileOut << temp;
	fileOut << LTC->getHocKy();
	fileOut << temp;
	fileOut << LTC->getNhom();
	fileOut << temp;
	fileOut << LTC->getSVMax();
	fileOut << temp;
	fileOut << LTC->getSVMin();
	fileOut << temp;
	fileOut << LTC->getTrangThai();
	fileOut << "\n";
}

void DSLopTC::writeDataDS_LTC(){
	ofstream fileOut;
	fileOut.open(PATH_SAVE_LTC, ios::out);
	if (fileOut.is_open()) {
		for (int i = 0; i < this->n; i++) 
			writeData_LTC(this->lopTC[i], fileOut);
		
	}
	fileOut.close();
}

