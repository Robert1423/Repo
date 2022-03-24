#include "dma.h"
#include <iostream>
#include <cstring>
DMA::DMA(const char * l, int r)
{
    label=new char[std::strlen(l)+1];
    std::strcpy(label,l);
    rating=r;
}
DMA::DMA(const DMA & rs)
{
    label=new char[std::strlen(rs.label)+1];
    std::strcpy(label,rs.label);
    rating=rs.rating;
}
DMA::~DMA()
{
    delete [] label;
}
void DMA::View() const
{
    std::cout<<"Etykietka: "<<label<<std::endl;
    std::cout<<"Klasa: "<<rating<<std::endl;
}
DMA & DMA::operator=(const DMA & rs)
{
    if (this==&rs)
        return *this;
    delete [] label;
    label = new char[std::strlen(rs.label)+1];
    std::strcpy(label,rs.label);
    rating=rs.rating;
    return *this;
}
//metody baseDMA
baseDMA::baseDMA(const char * l, int r) : DMA(l,r) {}
baseDMA::baseDMA(const baseDMA & rs) : DMA(rs) {}
baseDMA::~baseDMA() {}
baseDMA & baseDMA::operator=(const baseDMA & rs)
{
    DMA::operator=(rs);
    return *this;
}
void baseDMA::View() const
{
    DMA::View();
}
//metody lacksDMA
lacksDMA::lacksDMA(const char * c, const char * l, int r) : DMA(l,r)
{
    std::strncpy(color, c, 39);
    color[39]='\0';
}
lacksDMA::lacksDMA(const char * c, const DMA & rs)
: DMA(rs)
{
    std::strncpy(color, c, COL_LEN - 1);
    color[COL_LEN]='\0';
}
void lacksDMA::View() const
{
    DMA::View();
    std::cout<<"Kolor: "<<color<<std::endl;
}
//metody hasDMA
hasDMA::hasDMA(const char * s, const char * l, int r) : DMA(l,r)
{
    style=new char[std::strlen(s)+1];
    std::strcpy(style,s);
}
hasDMA::hasDMA(const char * s, const DMA & rs) : DMA(rs)
{
    style=new char[std::strlen(s)+1];
    std::strcpy(style,s);
}
hasDMA::hasDMA(const hasDMA & hs) : DMA(hs)
{
    style=new char[std::strlen(hs.style)+1];
    std::strcpy(style,hs.style);
}
hasDMA::~hasDMA()
{
    delete [] style;
}
hasDMA & hasDMA::operator=(const hasDMA & hs)
{
    if (this==&hs)
        return *this;
    DMA::operator=(hs);
    delete [] style;
    style=new char[std::strlen(hs.style)+1];
    std::strcpy(style,hs.style);
    return *this;
}
void hasDMA::View() const
{
    DMA::View();
    std::cout<<"Styl: "<<style<<std::endl;
}
