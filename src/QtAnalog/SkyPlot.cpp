#include <qtanalog.h>

N::SkyPlot:: SkyPlot (QWidget * parent,Plan * p)
           : Widget  (          parent,       p)
{
  Configure ( ) ;
}

N::SkyPlot::~SkyPlot(void)
{
}

void N::SkyPlot::Configure (void)
{
  p_antialiased     = true                          ;
  noBlinkingSats    = 0                             ;
  p_marginScale     = 0.78f                         ;
  p_gridColor       = QColor ( 150, 150, 150, 255 ) ;
  p_gridWidth       = 3                             ;
  p_textMargin      = 10                            ;
  p_withGridLabels  = true                          ;
  p_ellipses        = 3                             ;
  p_crosses         = 3                             ;
  p_blinkIntervall  = 500                           ;
  p_satScale        = 0.03f                         ;
  p_fontScale       = 0.02f                         ;
  ///////////////////////////////////////////////////
  setBackgroundRole ( QPalette::Base )              ;
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  blinkTimer.setInterval( p_blinkIntervall ) ;
  nConnect( &blinkTimer , SIGNAL( timeout     () )   ,
             this       , SLOT  ( change_blink() ) ) ;
}

bool N::SkyPlot::FocusIn (void)
{
  AssignAction ( Label , windowTitle() ) ;
  return true                            ;
}

QSize N::SkyPlot::sizeHint (void) const
{
  return QSize ( 320 , 320 ) ;
}

void N::SkyPlot::setMarginScale(float scale)
{
  p_marginScale = scale ;
  Iamv ( update() )     ;
}

void N::SkyPlot::setSatelliteScale(float scale)
{
  p_satScale = scale ;
  Iamv ( update() )  ;
}

void N::SkyPlot::setFontScale(float scale)
{
  p_fontScale = scale ;
  Iamv ( update() )   ;
}

void N::SkyPlot::setGridColor(const QColor & color)
{
  p_gridColor = color ;
  Iamv ( update() )   ;
}

void N::SkyPlot::setGridWidth(int width)
{
  p_gridWidth = width ;
  Iamv ( update() )   ;
}

void N::SkyPlot::setEllipses(int no)
{
  p_ellipses = no   ;
  Iamv ( update() ) ;
}

void N::SkyPlot::setCrosses(int no)
{
  p_crosses = no    ;
  Iamv ( update() ) ;
}

void N::SkyPlot::setTextMargin(int margin)
{
  p_textMargin = margin ;
  Iamv ( update() )     ;
}

void N::SkyPlot::setBlinkIntervall(int intervall)
{
  p_blinkIntervall = intervall ;
  Iamv ( update() )            ;
}

void N::SkyPlot::setWithGridLabels(int withLabels)
{
  p_withGridLabels = withLabels ;
  Iamv ( update() )             ;
}

void N::SkyPlot::setAntialiased(int antialiased)
{
  p_antialiased = antialiased ;
  Iamv ( update() )           ;
}

float N::SkyPlot::marginScale(void)
{
  return p_marginScale ;
}

float N::SkyPlot::satelliteScale(void)
{
  return p_satScale ;
}

float N::SkyPlot::fontScale(void)
{
  return p_fontScale ;
}

QColor N::SkyPlot::gridColor(void)
{
  return p_gridColor ;
}

int N::SkyPlot::gridWidth(void)
{
  return p_gridWidth ;
}

int N::SkyPlot::ellipses(void)
{
  return p_ellipses ;
}

int N::SkyPlot::crosses(void)
{
  return p_crosses ;
}

int N::SkyPlot::textMargin(void)
{
  return p_textMargin ;
}

int N::SkyPlot::blinkIntervall(void)
{
  return p_blinkIntervall ;
}

int N::SkyPlot::withGridLabels(void)
{
  return p_withGridLabels ;
}

int N::SkyPlot::antialiased(void)
{
  return p_antialiased ;
}

void N::SkyPlot::change_blink(void)
{
  if ( blink ) blink = false ;
          else blink = true  ;
  Iamv ( update() )          ;
}

void N::SkyPlot::paintEvent(QPaintEvent *)
{
   QSize          widgetSize( this->size() );
   QPainter       painter(this);
   float          topMargin ;
   float          leftMargin;
   float          size;
   float          satelliteSize;
   float          fontSize;

   if( widgetSize.height() > widgetSize.width() )
   {
      size = widgetSize.width() * p_marginScale;
      topMargin   = ( widgetSize.width() - widgetSize.width() * p_marginScale + widgetSize.height() - widgetSize.width() ) / 2;
      leftMargin  = ( widgetSize.width() - widgetSize.width() * p_marginScale ) / 2;
   }
   else
   {
      size = widgetSize.height() * p_marginScale;
      leftMargin = ( widgetSize.height() - widgetSize.height() * p_marginScale + widgetSize.width() - widgetSize.height()) / 2;
      topMargin  = ( widgetSize.height() - widgetSize.height() * p_marginScale ) / 2;
   }

   painter.setRenderHint(QPainter::Antialiasing, p_antialiased);
   painter.translate( leftMargin, topMargin );
   fontSize = size * p_fontScale;

   painter.setPen( QPen( p_gridColor, p_gridWidth ) );  
   painter.setFont( QFont( "Arial", (int)fontSize ) );
   for( int i=0; i < p_ellipses; i++ )
   {
      float radius = size / 2 - i * ( size / (2  * p_ellipses )  );
      painter.drawEllipse(  QPoint( size/2, size/2 ), (int)radius, (int)radius );
      if( p_withGridLabels )
         painter.drawText( QPoint( size/2 + p_textMargin, size/2 - ( radius + p_textMargin ) ),  
                           QString("%1").arg( i * (90 / p_ellipses ) ) );
   }

   for( int i=0; i < p_crosses; i ++ )
   {
      QLineF line1;
      QLineF line2;
      float angel = i * 90 / p_crosses;
      line1.setP1( QPoint( size/2, size/2 ) );
      line1.setLength( size/2 );

      QRectF textRect( 0, 0, 4 * fontSize, fontSize + 2 );

      line1.setAngle( angel + 90 );
      painter.drawLine( line1 );
      if( p_withGridLabels  )
      {
         line2 = QLineF( line1 );
         line2.setLength( size/2 + 2 * fontSize );
         textRect.moveCenter( line2.p2() );
         if( i > 0 )
            painter.drawText( textRect, Qt::AlignCenter, QString( "%1").arg( 360 - angel ) );
         else
            painter.drawText( textRect, Qt::AlignCenter, QString( "N") );
      }

      line1 = line1.normalVector();
      painter.drawLine( line1 );
      if( p_withGridLabels )
      {
         line2 = QLineF( line1 );
         line2.setLength( size/2 + 2 * fontSize );
         textRect.moveCenter( line2.p2() );
         if( i > 0 )
            painter.drawText( textRect, Qt::AlignCenter, QString( "%1").arg( 360 - 90 - angel ) );
         else
            painter.drawText( textRect, Qt::AlignCenter, QString( "W") );

      }

      line1 = line1.normalVector();
      painter.drawLine( line1 );
      if( p_withGridLabels )
      {
         line2 = QLineF( line1 );
         line2.setLength( size/2 + 2 * fontSize );
         textRect.moveCenter( line2.p2() );
         if( i > 0 )
            painter.drawText( textRect, Qt::AlignCenter, QString( "%1").arg( 360 - 180 - angel ) );
         else
            painter.drawText( textRect, Qt::AlignCenter, QString( "S") );
      }

      line1 = line1.normalVector();
      painter.drawLine( line1 );
      if( p_withGridLabels )
      {
         line2 = QLineF( line1 );
         line2.setLength( size/2 + 2 * fontSize );
         textRect.moveCenter( line2.p2() );
         if( i > 0 )
            painter.drawText( textRect, Qt::AlignCenter, QString( "%1").arg( 360 - 270 - angel ) );
         else
            painter.drawText( textRect, Qt::AlignCenter, QString( "E") );
      }

   }

   QBrush innerBrush = QBrush( Qt::SolidPattern );
   QBrush outerBrush = QBrush( );

   satelliteSize = size * p_satScale;

   for( I_satellite i= satellites.begin(); i != satellites.end(); i++ )
   {
      float el_s     = ( 90 - i->el ) * size / ( 2 * 90.0 );
      QRectF labelRect( 0, 0, i->label.length() * satelliteSize, satelliteSize+2 );

      QPoint satPos( size/2   + sin( i->az * 2 * M_PI / 360 ) * el_s,
                     size/2   - cos( i->az * 2 * M_PI / 360 ) * el_s );

      if(      ( i->state1 && i->blinking && blink )
            || ( i->state1 && !i->blinking         ) )
      {
         innerBrush.setColor( i->innerColor );
         painter.setBrush( innerBrush );
         painter.setPen( QPen( p_gridColor, 0 ) );  
         painter.drawEllipse( satPos, (int)satelliteSize, (int)satelliteSize );
      }

      if(      ( i->state2 && i->blinking && blink )
            || ( i->state2 && !i->blinking         ) )
      {
         painter.setBrush( outerBrush );
         painter.setPen( QPen( i->outerColor, satelliteSize/4 ) );  
         painter.drawEllipse( satPos, (int)satelliteSize, (int)satelliteSize );
      
      }

      if( ( i->blinking && blink ) || !i->blinking )
      {
         painter.setPen( QPen( i->fontColor, 2 ) );
         painter.setFont( QFont( "Arial", (int)satelliteSize, QFont::Bold ) );
         labelRect.moveCenter( satPos );
         painter.drawText( labelRect, Qt::AlignCenter, i->label );
      }
   }

}

void N::SkyPlot::addSatellite     (
       int             id         ,
       float           az         ,
       float           el         ,
       const QString & label      ,
       const QColor  & outerColor ,
       const QColor  & innerColor ,
       const QColor  & fontColor  ,
       bool            state1     ,
       bool            state2     ,
       bool            state3     ,
       bool            blinking   )
{
  Satellite sat                            ;
  sat.label      = label                   ;
  sat.az         = az                      ;
  sat.el         = el                      ;
  sat.state1     = state1                  ;
  sat.state2     = state2                  ;
  sat.state3     = state3                  ;
  sat.blinking   = blinking                ;
  sat.innerColor = innerColor              ;
  sat.outerColor = outerColor              ;
  sat.fontColor  = fontColor               ;
  if ( state3 )                            {
    sat.innerColor.setAlphaF( 1.0 )        ;
    sat.outerColor.setAlphaF( 1.0 )        ;
    sat.fontColor .setAlphaF( 1.0 )        ;
  } else                                   {
    sat.innerColor.setAlphaF( 0.3 )        ;
    sat.outerColor.setAlphaF( 0.3 )        ;
    sat.fontColor .setAlphaF( 0.3 )        ;
  }                                        ;
  if ( blinking )                          {
    if ( noBlinkingSats == 0)              {
      blinkTimer.start( p_blinkIntervall ) ;
    }                                      ;
    noBlinkingSats++                       ;
  } else Iamv ( update() )                 ;
  satellites.insert( id, sat )             ;
}

void N::SkyPlot::setSatBlinking(int id,bool state)
{
  if ( satellites.contains( id ) )             {
    if ( satellites[ id ].blinking && !state ) {
      if ( (--noBlinkingSats) == 0 )           {
        blinkTimer.stop()                      ;
      }                                        ;
      satellites[ id ].blinking = state        ;
    } else
    if ( !satellites[ id ].blinking && state ) {
      if ( noBlinkingSats == 0)                {
        blinkTimer.start( p_blinkIntervall )   ;
      }                                        ;
      noBlinkingSats++                         ;
      satellites[ id ].blinking = state        ;
    }                                          ;
  }                                            ;
}

bool N::SkyPlot::satIsBlinking(int id)
{
  if ( satellites.contains( id ) )   {
    return satellites[ id ].blinking ;
  } else return false                ;
}

void N::SkyPlot::removeSatellite(int id)
{
  if ( satellites.contains( id ) )   {
    if ( satellites[ id ].blinking ) {
      if ( (--noBlinkingSats) == 0 ) {
        blinkTimer.stop()            ;
      }                              ;
    }                                ;
    satellites.remove( id )          ;
  }                                  ;
}

QColor N::SkyPlot::satInnerColor(int id)
{
  if ( satellites.contains( id ) )     {
    return satellites[ id ].innerColor ;
  } else return QColor( 0, 0, 0 )      ;
}

QColor N::SkyPlot::satOuterColor(int id)
{
  if ( satellites.contains( id ) )     {
    return satellites[ id ].outerColor ;
  } else return QColor( 0, 0, 0 )      ;
}

QColor N::SkyPlot::satFontColor(int id)
{
  if ( satellites.contains( id ) )    {
    return satellites[ id ].fontColor ;
  } else return QColor( 0, 0, 0 )     ;
}

void N::SkyPlot::setSatInnerColor(int id,const QColor & c)
{
  if ( satellites.contains( id ) )  {
    satellites[ id ].innerColor = c ;
  }                                 ;
  Iamv ( update() )                 ;
}

void N::SkyPlot::setSatOuterColor(int id,const QColor & c)
{
  if ( satellites.contains( id ) )  {
    satellites[ id ].outerColor = c ;
  }                                 ;
  Iamv ( update() )                 ;
}

void N::SkyPlot::setSatFontColor(int id,const QColor & c)
{
  if ( satellites.contains( id ) ) {
    satellites[ id ].fontColor = c ;
  }                                ;
  Iamv ( update() )                ;
}

bool N::SkyPlot::satState1(int id)
{
  if ( satellites.contains( id ) ) {
    return satellites[ id ].state1 ;
  } else return false              ;
}

bool N::SkyPlot::satState2(int id)
{
  if ( satellites.contains( id ) ) {
    return satellites[ id ].state2 ;
  } else return false              ;
}

bool N::SkyPlot::satState3(int id)
{
  if ( satellites.contains( id ) ) {
    return satellites[ id ].state3 ;
  } else return false              ;
}

void N::SkyPlot::setSatState1(int id,bool state)
{
  if ( satellites.contains( id ) )  {
    satellites[ id ].state1 = state ;
  }                                 ;
  Iamv ( update() )                 ;
}

void N::SkyPlot::setSatState2(int id,bool state)
{
  if ( satellites.contains( id ) )  {
    satellites[ id ].state2 = state ;
  }                                 ;
  Iamv ( update() )                 ;
}

void N::SkyPlot::setSatState3(int id,bool state)
{
  if ( satellites.contains( id ) )  {
    satellites[ id ].state3 = state ;
  }                                 ;
  Iamv ( update() )                 ;
}

QString N::SkyPlot::satLabel(int id)
{
  if ( satellites.contains( id ) ) {
    return satellites[ id ].label  ;
  } else return QString ( "" )     ;
}

void N::SkyPlot::setSatLabel(int id,const QString & label)
{
  if ( satellites.contains( id ) ) {
    satellites[ id ].label = label ;
  }                                ;
  Iamv ( update() )                ;
}

float N::SkyPlot::satAzimuth(int id)
{
  if ( satellites.contains( id ) ) {
    return satellites[ id ].az     ;
  } else return 0.0                ;
}

float N::SkyPlot::satElevation(int id)
{
  if ( satellites.contains( id ) ) {
    return satellites[ id ].el     ;
  } else return 0.0                ;
}

void N::SkyPlot::setSatAzimuth( int id, float az )
{
  if ( satellites.contains( id ) ) {
    satellites[ id ].az = az       ;
  }                                ;
  Iamv ( update() )                ;
}

void N::SkyPlot::setSatElevation(int id,float el)
{
  if ( satellites.contains( id ) ) {
    satellites[ id ].el = el       ;
  }                                ;
  Iamv ( update() )                ;
}
