/****************************************************************************
 *                                                                          *
 * Copyright (C) 2015 Neutrino International Inc.                           *
 *                                                                          *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin            *
 *                                                                          *
 ****************************************************************************/

#ifndef QT_ANALOG_H
#define QT_ANALOG_H

#include <QtManagers>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_QTANALOG_LIB)
#      define Q_ANALOG_EXPORT Q_DECL_EXPORT
#    else
#      define Q_ANALOG_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define Q_ANALOG_EXPORT
#endif

namespace N
{

class Q_ANALOG_EXPORT SkyPlot ;

class Q_ANALOG_EXPORT SkyPlot : public Widget
{
  Q_OBJECT
  Q_PROPERTY( float  marginScale       READ marginScale     WRITE setMarginScale    )
  Q_PROPERTY( float  satelliteScale    READ satelliteScale  WRITE setSatelliteScale )
  Q_PROPERTY( float  fontScale         READ fontScale       WRITE setFontScale      )
  Q_PROPERTY( QColor gridColor         READ gridColor       WRITE setGridColor      )
  Q_PROPERTY( int    gridWidth         READ gridWidth       WRITE setGridWidth      )
  Q_PROPERTY( int    ellipses          READ ellipses        WRITE setEllipses       )
  Q_PROPERTY( int    crosses           READ crosses         WRITE setCrosses        )
  Q_PROPERTY( int    textMargin        READ textMargin      WRITE setTextMargin     )
  Q_PROPERTY( int    blinkIntervall    READ blinkIntervall  WRITE setBlinkIntervall )
  Q_PROPERTY( bool   withGridLabels    READ withGridLabels  WRITE setWithGridLabels )
  Q_PROPERTY( bool   antialiased       READ antialiased     WRITE setAntialiased    )
  public:

    explicit      SkyPlot           (StandardConstructor) ;
    virtual      ~SkyPlot           (void) ;

    virtual QSize sizeHint          (void) const ;

    void          addSatellite      (int              id         ,
                                     float            az         ,
                                     float            el         ,
                                     const QString  & label      ,
                                     const QColor   & outerColor ,
                                     const QColor   & innerColor ,
                                     const QColor   & fontColor  ,
                                     bool  state1   = true       ,
                                     bool  state2   = true       ,
                                     bool  state3   = true       ,
                                     bool  blinking = true     ) ;

    void          removeSatellite   (int id) ;

    void          setMarginScale    (float scale) ;
    void          setSatelliteScale (float scale) ;
    void          setFontScale      (float scale) ;
    void          setGridColor      (const QColor & color) ;
    void          setGridWidth      (int width) ;
    void          setEllipses       (int no) ;
    void          setCrosses        (int no) ;
    void          setTextMargin     (int margin) ;
    void          setBlinkIntervall (int intervall) ;
    void          setWithGridLabels (int withLabels) ;
    void          setAntialiased    (int antialiased) ;

    float         marginScale       (void) ;
    float         satelliteScale    (void) ;
    float         fontScale         (void) ;
    QColor        gridColor         (void) ;
    int           gridWidth         (void) ;
    int           ellipses          (void) ;
    int           crosses           (void) ;
    int           textMargin        (void) ;
    int           blinkIntervall    (void) ;
    int           withGridLabels    (void) ;
    int           antialiased       (void) ;

    bool          satIsBlinking     (int id) ;
    QColor        satInnerColor     (int id) ;
    QColor        satOuterColor     (int id) ;
    QColor        satFontColor      (int id) ;
    bool          satState1         (int id) ;
    bool          satState2         (int id) ;
    bool          satState3         (int id) ;
    QString       satLabel          (int id) ;
    float         satAzimuth        (int id) ;
    float         satElevation      (int id) ;

    void          setSatBlinking    (int id,bool  state          ) ;
    void          setSatInnerColor  (int id,const QColor & c     ) ;
    void          setSatOuterColor  (int id,const QColor & c     ) ;
    void          setSatFontColor   (int id,const QColor & c     ) ;
    void          setSatState1      (int id,bool  state          ) ;
    void          setSatState2      (int id,bool  state          ) ;
    void          setSatState3      (int id,bool  state          ) ;
    void          setSatLabel       (int id,const QString & label) ;
    void          setSatAzimuth     (int id,float az             ) ;
    void          setSatElevation   (int id,float el             ) ;

  protected:

    virtual void  Configure         (void) ;
    virtual bool  FocusIn           (void) ;

    virtual void  paintEvent        (QPaintEvent * event) ;

  private:

    int       noBlinkingSats;
    bool      blink;
    QTimer    blinkTimer;

    float     p_marginScale;
    float     p_satScale;
    float     p_fontScale;
    QColor    p_gridColor;
    int       p_gridWidth;
    int       p_ellipses;
    int       p_crosses;
    int       p_textMargin;
    int       p_blinkIntervall;
    bool      p_withGridLabels;
    bool      p_antialiased;

    typedef struct _Satellite {
      QString label           ;
      QColor  innerColor      ;
      QColor  outerColor      ;
      QColor  fontColor       ;
      float   az              ;
      float   el              ;
      bool    state1          ;
      bool    state2          ;
      bool    state3          ;
      bool    blinking        ;
    } Satellite               ;

    QMap         < int, Satellite >                   satellites  ;
    typedef QMap < int, Satellite > :: const_iterator I_satellite ;

  public slots:

  private slots:

  private slots:

    void change_blink( void );

  signals:

};

}

QT_END_NAMESPACE

#endif
