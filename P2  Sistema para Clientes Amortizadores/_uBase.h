#if !defined __UBASE_H_
#define __UBASE_H_

class cBase{
private:
    int TodoCorrecto;
public:
    cBase();
    virtual void Ejecuta() = 0;

    void mRegistraError();
    void mRegistraExito();
    int mTodoCorrecto();

};

class cEjecutor{
public:
    void Ahora(cBase *pvObjeto);
};

#endif
