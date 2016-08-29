#include "bthreadengine.h"
#include <assert.h>
namespace Bigo {
    BThreadEngine::BThreadEngine(QObject *parent,BThreadTaskItem * pTaskItem,int nThreads,bool bFIFOKeep)
        : QObject(parent),
        m_pThreadTaskItem(pTaskItem),
        m_nThreads(nThreads),
        m_bFIFOKeep(bFIFOKeep)
    {
        assert(nThreads>0 && nThreads<512);
        //创建固定数目的线程
        for (int i=0;i<nThreads;i++)
        {
            QThread * pNewThread = new QThread(this);
            BThreadObject * pNewObject = new BThreadObject(0,pTaskItem);
            //记录下来
            m_ThreadPool.push_back(pNewThread);
            m_ThreadObjs.push_back(pNewObject);
            m_map_Tasks[pNewObject] = 0;
            pNewThread->start();
            //把QGHThreadObject的信号、曹处理搬移到子线程内
            pNewObject->moveToThread(pNewThread);
            //连接处理完成消息
            connect(pNewObject,SIGNAL(sig_process_finished(BdynObj *)),this,SLOT(on_sig_process_finished(BdynObj *)));
            //连接处理新任务消息
            connect(this,SIGNAL(do_task(BdynObj *, QObject *)),pNewObject,SLOT(process(BdynObj *, QObject *)));

        }
    }

    BThreadEngine::~BThreadEngine()
    {
        foreach(BThreadObject * obj,m_ThreadObjs)
        {
            disconnect(obj,SIGNAL(sig_process_finished(BdynObj *)),this,SLOT(on_sig_process_finished(BdynObj *)));
            disconnect(this,SIGNAL(do_task(BdynObj *, QObject *)),obj,SLOT(process(BdynObj *, QObject *)));
            obj->deleteLater();
        }
        foreach(QThread * th ,m_ThreadPool)
        {
//            disconnect(this,SIGNAL(do_task(BdynObj *, QObject *)),th,SLOT(process(BdynObj *, QObject *)));
            th->exit(0);
            th->wait();
        }
    }
    void BThreadEngine::append_new(BdynObj *data_source)
    {
        QObject * pMinObj = 0;
        data_source->lock();
        //对一批来自同一数据源的数据，使用同样的数据源处理，以免发生多线程扰乱FIFO对单个data_source的完整性
        if (m_map_busy_source_counter.find(data_source)!=m_map_busy_source_counter.end()&& m_bFIFOKeep==true)
        {

            m_map_busy_source_counter[data_source]++;
            pMinObj = m_map_busy_source_task[data_source];
        }
        else
        {
            qint32 nMinCost = 0x7fffffff;
            //寻找现在最空闲的一个线程
            for (QMap<QObject *,qint32>::iterator p = m_map_Tasks.begin();p!=m_map_Tasks.end();p++)
            {
                if (p.value()< nMinCost)
                {
                    nMinCost = p.value();
                    pMinObj = p.key();
                }
            }
            if (pMinObj)
            {
                m_map_busy_source_counter[data_source] = 1;
                m_map_busy_source_task[data_source] = pMinObj;
            }
        }
        if (pMinObj)
        {
            m_map_Tasks[pMinObj]++;
            emit do_task(data_source, pMinObj);
        }else {
            data_source->unlock();
        }
    }
    void BThreadEngine::on_sig_process_finished(BdynObj * data_source)
    {
        if (m_map_Tasks.find(sender())!=m_map_Tasks.end())
        {
            m_map_Tasks[sender()]--;
        }
        if (m_map_busy_source_counter.find(data_source)!=m_map_busy_source_counter.end())
        {
            m_map_busy_source_counter[data_source]--;
            if (m_map_busy_source_counter[data_source]<=0)
            {
                m_map_busy_source_counter.remove(data_source);
                m_map_busy_source_task.remove(data_source);
                data_source->unlock();
            }
        }
    }
}

