#ifndef BIMAGE_H
#define BIMAGE_H
#include "Bobject/bstatic.h"
namespace Bigo {

    class Bimage : public Bstatic
    {
        Q_OBJECT
    public:
        explicit Bimage(QWidget *parent = 0);
        explicit Bimage( QString path, QWidget *parent = 0);
    public: //virtual functions
        virtual void painting(QPainter &painter);

    public:
        void setPath(QString path);
        QString imgPath() const;
    signals:

    public slots:
    protected:
        QString m_path;
    };
}

#endif // BIMAGE_H
