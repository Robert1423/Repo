#ifndef DMA_H_
#define DMA_H_
#include <iostream>
class DMA
{
private:
    char * label;
    int rating;
public:
    DMA(const char * l="brak", int r=0);
    DMA(const DMA & rs);
    virtual ~DMA();
    virtual void View() const=0;
    DMA & operator=(const DMA & rs);
};
class baseDMA : public DMA
{
public:
    baseDMA(const char * l="brak", int r=0);
    baseDMA(const baseDMA & rs);
    ~baseDMA();
    baseDMA & operator=(const baseDMA & rs);
    virtual void View() const;
};
class lacksDMA : public DMA
{
private:
    enum {COL_LEN=40};
    char color[COL_LEN];
public:
    lacksDMA(const char * c="brak", const char * l="brak", int r=0);
    lacksDMA(const char * c, const DMA & rs);
    virtual void View() const;
};
class hasDMA : public DMA
{
private:
    char * style;
public:
    hasDMA(const char * s="brak", const char * l="brak", int r=0);
    hasDMA(const char * s, const DMA & rs);
    hasDMA(const hasDMA & hs);
    ~hasDMA();
    hasDMA & operator=(const hasDMA & hs);
    virtual void View() const;
};
#endif
