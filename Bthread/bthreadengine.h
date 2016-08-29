#ifndef BTHREADENGINE_H
#define BTHREADENGINE_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <QList>
#include <QMap>
#include <QMutex>
#include "Bobject/bdynobj.h"
#include "bthreadtaskitem.h"
#include "bthreadobject.h"


namespace Bigo {
//线程池引擎，帮助用户进行动态平衡
class BThreadEngine : public QObject
{
    Q_OBJECT
public:
    BThreadEngine(QObject *parent,BThreadTaskItem * pTaskItem,int nThreads = 2,bool bFIFOKeep = true);
    ~BThreadEngine();
protected:
    QVector<QThread *> m_ThreadPool;
    QVector<BThreadObject *> m_ThreadObjs;
    BThreadTaskItem * m_pThreadTaskItem;
    int m_nThreads;
    bool m_bFIFOKeep;
private:
    //各个m_ThreadPool\m_ThreadObjs的任务数
    QMap<QObject *,qint32> m_map_Tasks;
    //m_bFIFOKeep == true 时，下面两个成员将保证非空闲的单个 data_source 将始终在单一线程处理
    //各个data_source 目前的处理线程
    QMap<BdynObj *,QObject *> m_map_busy_source_task;
    //各个data_source 目前的排队数目
    QMap<BdynObj *,int> m_map_busy_source_counter;
public:
    void SetThreadTaskItem(BThreadTaskItem * pTaskItem);
    QList<qint32> CurrentLoad()
    {
        return m_map_Tasks.values();
    }
public slots:
    void append_new(BdynObj *data_source);
    //捕获BThreadObject::sig_process_finished, 以便管理data_source的 FIFO 顺序
    void on_sig_process_finished(BdynObj * data_source);
signals:
    //************************************
    // Method:    do_task
    // FullName:  QGHThreadEngine::do_task
    // Access:    public
    // Returns:   void
    // Qualifier:
    // Parameter: QObject *		任务来源 （相同任务源的任务，在队列非空时会被安排到同一个线程处理，以确保对相同源的FIFO）
    // Parameter: QByteArray	任务体
    // Parameter: QObject *		处理任务的线程对象（QGHThreadObject）
    //************************************
    void do_task(BdynObj *, QObject *);
};
}


#endif // BTHREADENGINE_H
