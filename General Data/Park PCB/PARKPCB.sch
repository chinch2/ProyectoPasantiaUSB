<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.3.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="101" name="Hidden" color="15" fill="1" visible="yes" active="yes"/>
<layer number="102" name="Changes" color="12" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="teensypp">
<packages>
<package name="TEENSY++">
<description>teensy ++</description>
<wire x1="25.4" y1="8.89" x2="-25.4" y2="8.89" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="-8.89" x2="25.4" y2="-8.89" width="0.1524" layer="21"/>
<wire x1="25.4" y1="8.89" x2="25.4" y2="6.35" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="8.89" x2="-25.4" y2="6.35" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="-8.89" x2="-25.4" y2="-6.35" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="1.016" x2="-25.4" y2="-1.016" width="0.1524" layer="21" curve="-180"/>
<wire x1="-25.4" y1="6.35" x2="-25.4" y2="1.016" width="0.1524" layer="21"/>
<wire x1="25.4" y1="6.35" x2="25.4" y2="-6.35" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="-6.35" x2="25.4" y2="-6.35" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="-6.35" x2="-25.4" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="25.4" y1="-6.35" x2="25.4" y2="-8.89" width="0.1524" layer="21"/>
<wire x1="-25.4" y1="6.35" x2="25.4" y2="6.35" width="0.1524" layer="21"/>
<pad name="GND" x="-24.13" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="B7" x="-21.59" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="D2" x="-13.97" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="D3" x="-11.43" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="D0" x="-19.05" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="D1" x="-16.51" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="D4" x="-8.89" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="D5" x="-6.35" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="D6" x="-3.81" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="D7" x="-1.27" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="E0" x="1.27" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="E1" x="3.81" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="C0" x="6.35" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="C1" x="8.89" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="C2" x="11.43" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="C3" x="13.97" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="C4" x="16.51" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="C5" x="19.05" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="C6" x="21.59" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="C7" x="24.13" y="-7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="F7" x="24.13" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="F6" x="21.59" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="F5" x="19.05" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="F4" x="16.51" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="F3" x="13.97" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="F2" x="11.43" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="F1" x="8.89" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="F0" x="6.35" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="REF" x="3.81" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="GRND1" x="1.27" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="E6" x="-1.27" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="E7" x="-3.81" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="B0" x="-6.35" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="B1" x="-8.89" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="B2" x="-11.43" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="B3" x="-13.97" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="B4" x="-16.51" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="B5" x="-19.05" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="B6" x="-21.59" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="+5V" x="-24.13" y="7.62" drill="0.8128" shape="long" rot="R90"/>
<pad name="A4" x="8.89" y="2.54" drill="0.8" shape="square"/>
<pad name="A5" x="11.43" y="2.54" drill="0.8" shape="square"/>
<pad name="A6" x="13.97" y="2.54" drill="0.8" shape="square"/>
<pad name="A7" x="16.51" y="2.54" drill="0.8" shape="square"/>
<pad name="A3" x="16.51" y="0" drill="0.8" shape="square"/>
<pad name="A2" x="13.97" y="0" drill="0.8" shape="square"/>
<pad name="A1" x="11.43" y="0" drill="0.8" shape="square"/>
<pad name="A0" x="8.89" y="0" drill="0.8" shape="square"/>
<pad name="RST" x="24.13" y="2.54" drill="0.8" shape="square"/>
<pad name="GND2" x="24.13" y="0" drill="0.8" shape="square"/>
<pad name="5V" x="24.13" y="-2.54" drill="0.8" shape="square"/>
<pad name="E4" x="-9.144" y="0.9144" drill="0.635" diameter="1.0668" rot="R180"/>
<pad name="E5" x="-9.144" y="-0.4064" drill="0.635" diameter="1.0668" rot="R180"/>
<text x="-22.225" y="-4.445" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-25.908" y="-8.255" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="ARDUNIO">
<wire x1="-22.86" y1="30.48" x2="17.78" y2="30.48" width="0.254" layer="94"/>
<wire x1="17.78" y1="30.48" x2="17.78" y2="-45.72" width="0.254" layer="94"/>
<wire x1="17.78" y1="-45.72" x2="-22.86" y2="-45.72" width="0.254" layer="94"/>
<wire x1="-22.86" y1="-45.72" x2="-22.86" y2="30.48" width="0.254" layer="94"/>
<text x="-20.32" y="33.02" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-15.24" size="1.778" layer="96" rot="R270">&gt;VALUE</text>
<pin name="GND" x="-27.94" y="27.94" length="middle" direction="pwr"/>
<pin name="27,PWM" x="-27.94" y="25.4" length="middle"/>
<pin name="0,PWM,INT0" x="-27.94" y="22.86" length="middle"/>
<pin name="1,PWM,INT1" x="-27.94" y="20.32" length="middle"/>
<pin name="2,RX,INT2" x="-27.94" y="17.78" length="middle"/>
<pin name="3,TX,INT3" x="-27.94" y="15.24" length="middle"/>
<pin name="4" x="-27.94" y="12.7" length="middle"/>
<pin name="5" x="-27.94" y="10.16" length="middle"/>
<pin name="6,LED" x="-27.94" y="7.62" length="middle"/>
<pin name="7" x="-27.94" y="5.08" length="middle"/>
<pin name="8" x="-27.94" y="2.54" length="middle"/>
<pin name="9" x="-27.94" y="0" length="middle"/>
<pin name="10" x="-27.94" y="-2.54" length="middle"/>
<pin name="11" x="-27.94" y="-5.08" length="middle"/>
<pin name="12" x="-27.94" y="-7.62" length="middle"/>
<pin name="13" x="-27.94" y="-10.16" length="middle"/>
<pin name="14,PWM" x="-27.94" y="-12.7" length="middle"/>
<pin name="15,PWM" x="-27.94" y="-15.24" length="middle"/>
<pin name="16,PWM" x="-27.94" y="-17.78" length="middle"/>
<pin name="17" x="-27.94" y="-20.32" length="middle"/>
<pin name="VCC" x="22.86" y="27.94" length="middle" direction="pwr" rot="R180"/>
<pin name="26,PWM" x="22.86" y="25.4" length="middle" rot="R180"/>
<pin name="25,PWM" x="22.86" y="22.86" length="middle" rot="R180"/>
<pin name="24,PWM" x="22.86" y="20.32" length="middle" rot="R180"/>
<pin name="23" x="22.86" y="17.78" length="middle" rot="R180"/>
<pin name="22" x="22.86" y="15.24" length="middle" rot="R180"/>
<pin name="21" x="22.86" y="12.7" length="middle" rot="R180"/>
<pin name="20" x="22.86" y="10.16" length="middle" rot="R180"/>
<pin name="19" x="22.86" y="7.62" length="middle" rot="R180"/>
<pin name="18,INT6" x="22.86" y="5.08" length="middle" rot="R180"/>
<pin name="GND@1" x="22.86" y="2.54" length="middle" direction="pwr" rot="R180"/>
<pin name="AREF" x="22.86" y="0" length="middle" direction="in" rot="R180"/>
<pin name="38,A0" x="22.86" y="-2.54" length="middle" rot="R180"/>
<pin name="39,A1" x="22.86" y="-5.08" length="middle" rot="R180"/>
<pin name="40,A2" x="22.86" y="-7.62" length="middle" rot="R180"/>
<pin name="41,A3" x="22.86" y="-10.16" length="middle" rot="R180"/>
<pin name="42,A4" x="22.86" y="-12.7" length="middle" rot="R180"/>
<pin name="43,A5" x="22.86" y="-15.24" length="middle" rot="R180"/>
<pin name="44,A6" x="22.86" y="-17.78" length="middle" rot="R180"/>
<pin name="45,A7" x="22.86" y="-20.32" length="middle" rot="R180"/>
<pin name="28" x="22.86" y="-25.4" length="middle" rot="R180"/>
<pin name="29" x="22.86" y="-27.94" length="middle" rot="R180"/>
<pin name="30" x="22.86" y="-30.48" length="middle" rot="R180"/>
<pin name="31" x="22.86" y="-33.02" length="middle" rot="R180"/>
<pin name="32" x="22.86" y="-35.56" length="middle" rot="R180"/>
<pin name="33" x="22.86" y="-38.1" length="middle" rot="R180"/>
<pin name="34" x="22.86" y="-40.64" length="middle" rot="R180"/>
<pin name="35" x="22.86" y="-43.18" length="middle" rot="R180"/>
<pin name="_RST" x="-27.94" y="-25.4" length="middle" direction="in"/>
<pin name="_GND2" x="-27.94" y="-27.94" length="middle" direction="pwr"/>
<pin name="+5V" x="-27.94" y="-30.48" length="middle" direction="pwr"/>
<pin name="36,INT4" x="-27.94" y="-35.56" length="middle"/>
<pin name="37,INT5" x="-27.94" y="-38.1" length="middle"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="ARDUINO-TEENSY++">
<gates>
<gate name="G$1" symbol="ARDUNIO" x="-2.54" y="15.24"/>
</gates>
<devices>
<device name="" package="TEENSY++">
<connects>
<connect gate="G$1" pin="+5V" pad="+5V"/>
<connect gate="G$1" pin="0,PWM,INT0" pad="D0"/>
<connect gate="G$1" pin="1,PWM,INT1" pad="D1"/>
<connect gate="G$1" pin="10" pad="C0"/>
<connect gate="G$1" pin="11" pad="C1"/>
<connect gate="G$1" pin="12" pad="C2"/>
<connect gate="G$1" pin="13" pad="C3"/>
<connect gate="G$1" pin="14,PWM" pad="C4"/>
<connect gate="G$1" pin="15,PWM" pad="C5"/>
<connect gate="G$1" pin="16,PWM" pad="C6"/>
<connect gate="G$1" pin="17" pad="C7"/>
<connect gate="G$1" pin="18,INT6" pad="E6"/>
<connect gate="G$1" pin="19" pad="E7"/>
<connect gate="G$1" pin="2,RX,INT2" pad="D2"/>
<connect gate="G$1" pin="20" pad="B0"/>
<connect gate="G$1" pin="21" pad="B1"/>
<connect gate="G$1" pin="22" pad="B2"/>
<connect gate="G$1" pin="23" pad="B3"/>
<connect gate="G$1" pin="24,PWM" pad="B4"/>
<connect gate="G$1" pin="25,PWM" pad="B5"/>
<connect gate="G$1" pin="26,PWM" pad="B6"/>
<connect gate="G$1" pin="27,PWM" pad="B7"/>
<connect gate="G$1" pin="28" pad="A0"/>
<connect gate="G$1" pin="29" pad="A1"/>
<connect gate="G$1" pin="3,TX,INT3" pad="D3"/>
<connect gate="G$1" pin="30" pad="A2"/>
<connect gate="G$1" pin="31" pad="A3"/>
<connect gate="G$1" pin="32" pad="A4"/>
<connect gate="G$1" pin="33" pad="A5"/>
<connect gate="G$1" pin="34" pad="A6"/>
<connect gate="G$1" pin="35" pad="A7"/>
<connect gate="G$1" pin="36,INT4" pad="E4"/>
<connect gate="G$1" pin="37,INT5" pad="E5"/>
<connect gate="G$1" pin="38,A0" pad="F0"/>
<connect gate="G$1" pin="39,A1" pad="F1"/>
<connect gate="G$1" pin="4" pad="D4"/>
<connect gate="G$1" pin="40,A2" pad="F2"/>
<connect gate="G$1" pin="41,A3" pad="F3"/>
<connect gate="G$1" pin="42,A4" pad="F4"/>
<connect gate="G$1" pin="43,A5" pad="F5"/>
<connect gate="G$1" pin="44,A6" pad="F6"/>
<connect gate="G$1" pin="45,A7" pad="F7"/>
<connect gate="G$1" pin="5" pad="D5"/>
<connect gate="G$1" pin="6,LED" pad="D6"/>
<connect gate="G$1" pin="7" pad="D7"/>
<connect gate="G$1" pin="8" pad="E0"/>
<connect gate="G$1" pin="9" pad="E1"/>
<connect gate="G$1" pin="AREF" pad="REF"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="GND@1" pad="GRND1"/>
<connect gate="G$1" pin="VCC" pad="5V"/>
<connect gate="G$1" pin="_GND2" pad="GND2"/>
<connect gate="G$1" pin="_RST" pad="RST"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="i2c">
<description>&lt;b&gt;I²C Bus Devices&lt;/b&gt;
&lt;p&gt;
See &lt;a href="http://www.philipslogic.com/products/i2c/"&gt;http://www.philipslogic.com/products/i2c/&lt;/a&gt; for more devices.
&lt;p&gt;
Version history:&lt;br&gt;
02 Jun 2004 v1.00 Created by Eelco Huininga (&lt;a href="mailto:eelcapone@beer.com"&gt;eelcapone@NOSPAMbeer.com&lt;/a&gt;)&lt;br&gt;
30 Aug 2004 v1.01 Updated by P. Klaja (added PCF8583)&lt;br&gt;
04 Dec 2004 v1.02 Updated by Eelco Huininga (added 82B715)&lt;br&gt;
19 Dec 2004 v1.03 Bugfix: 82B715 package SO08 had pin 6 and 7 swapped&lt;br&gt;</description>
<packages>
<package name="DIL16">
<wire x1="10.16" y1="2.921" x2="-10.16" y2="2.921" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-2.921" x2="10.16" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="10.16" y1="2.921" x2="10.16" y2="-2.921" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="2.921" x2="-10.16" y2="1.016" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="-2.921" x2="-10.16" y2="-1.016" width="0.1524" layer="21"/>
<wire x1="-10.16" y1="1.016" x2="-10.16" y2="-1.016" width="0.1524" layer="21" curve="-180"/>
<pad name="1" x="-8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="2" x="-6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="7" x="6.35" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="8" x="8.89" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="3" x="-3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="4" x="-1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="6" x="3.81" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="5" x="1.27" y="-3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="9" x="8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="10" x="6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="11" x="3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="12" x="1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="13" x="-1.27" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="14" x="-3.81" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="15" x="-6.35" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<pad name="16" x="-8.89" y="3.81" drill="0.8128" shape="long" rot="R90"/>
<text x="-10.541" y="-2.921" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="-7.493" y="-0.635" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
</package>
<package name="SO16">
<wire x1="4.699" y1="1.9558" x2="-4.699" y2="1.9558" width="0.1524" layer="51"/>
<wire x1="4.699" y1="-1.9558" x2="5.08" y2="-1.5748" width="0.1524" layer="21" curve="90" cap="flat"/>
<wire x1="-5.08" y1="1.5748" x2="-4.699" y2="1.9558" width="0.1524" layer="21" curve="-90" cap="flat"/>
<wire x1="4.699" y1="1.9558" x2="5.08" y2="1.5748" width="0.1524" layer="21" curve="-90" cap="flat"/>
<wire x1="-5.08" y1="-1.5748" x2="-4.699" y2="-1.9558" width="0.1524" layer="21" curve="90" cap="flat"/>
<wire x1="-4.699" y1="-1.9558" x2="4.699" y2="-1.9558" width="0.1524" layer="51"/>
<wire x1="5.08" y1="-1.5748" x2="5.08" y2="1.5748" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="1.5748" x2="-5.08" y2="-1.5748" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.508" x2="-5.08" y2="-0.508" width="0.1524" layer="21" curve="-180"/>
<wire x1="-5.08" y1="-1.6002" x2="5.08" y2="-1.6002" width="0.0508" layer="21"/>
<smd name="1" x="-4.445" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="16" x="-4.445" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="2" x="-3.175" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="3" x="-1.905" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="15" x="-3.175" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="14" x="-1.905" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="4" x="-0.635" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="13" x="-0.635" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="5" x="0.635" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="12" x="0.635" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="6" x="1.905" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="7" x="3.175" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="11" x="1.905" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="10" x="3.175" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="8" x="4.445" y="-3.0734" dx="0.6604" dy="2.032" layer="1"/>
<smd name="9" x="4.445" y="3.0734" dx="0.6604" dy="2.032" layer="1"/>
<text x="-3.81" y="-0.762" size="1.27" layer="27" ratio="10">&gt;VALUE</text>
<text x="-5.461" y="-1.905" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<rectangle x1="-0.889" y1="1.9558" x2="-0.381" y2="3.0988" layer="51"/>
<rectangle x1="-4.699" y1="-3.0988" x2="-4.191" y2="-1.9558" layer="51"/>
<rectangle x1="-3.429" y1="-3.0988" x2="-2.921" y2="-1.9558" layer="51"/>
<rectangle x1="-2.159" y1="-3.0734" x2="-1.651" y2="-1.9304" layer="51"/>
<rectangle x1="-0.889" y1="-3.0988" x2="-0.381" y2="-1.9558" layer="51"/>
<rectangle x1="-2.159" y1="1.9558" x2="-1.651" y2="3.0988" layer="51"/>
<rectangle x1="-3.429" y1="1.9558" x2="-2.921" y2="3.0988" layer="51"/>
<rectangle x1="-4.699" y1="1.9558" x2="-4.191" y2="3.0988" layer="51"/>
<rectangle x1="0.381" y1="-3.0988" x2="0.889" y2="-1.9558" layer="51"/>
<rectangle x1="1.651" y1="-3.0988" x2="2.159" y2="-1.9558" layer="51"/>
<rectangle x1="2.921" y1="-3.0988" x2="3.429" y2="-1.9558" layer="51"/>
<rectangle x1="4.191" y1="-3.0988" x2="4.699" y2="-1.9558" layer="51"/>
<rectangle x1="0.381" y1="1.9558" x2="0.889" y2="3.0988" layer="51"/>
<rectangle x1="1.651" y1="1.9558" x2="2.159" y2="3.0988" layer="51"/>
<rectangle x1="2.921" y1="1.9558" x2="3.429" y2="3.0988" layer="51"/>
<rectangle x1="4.191" y1="1.9558" x2="4.699" y2="3.0988" layer="51"/>
</package>
</packages>
<symbols>
<symbol name="PCF8574">
<wire x1="-7.62" y1="12.7" x2="-7.62" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-10.16" x2="7.62" y2="-10.16" width="0.254" layer="94"/>
<wire x1="7.62" y1="-10.16" x2="7.62" y2="12.7" width="0.254" layer="94"/>
<wire x1="7.62" y1="12.7" x2="-7.62" y2="12.7" width="0.254" layer="94"/>
<text x="-2.54" y="15.24" size="1.778" layer="95">&gt;NAME</text>
<text x="-5.08" y="-12.7" size="1.778" layer="96">&gt;VALUE</text>
<pin name="/INT" x="-10.16" y="10.16" length="short" direction="out" function="dot"/>
<pin name="A0" x="-10.16" y="5.08" length="short" direction="in"/>
<pin name="A1" x="-10.16" y="2.54" length="short" direction="in"/>
<pin name="A2" x="-10.16" y="0" length="short" direction="in"/>
<pin name="SCL" x="-10.16" y="-5.08" length="short" direction="in"/>
<pin name="SDA" x="-10.16" y="-7.62" length="short"/>
<pin name="P0" x="10.16" y="10.16" length="short" rot="R180"/>
<pin name="P1" x="10.16" y="7.62" length="short" rot="R180"/>
<pin name="P2" x="10.16" y="5.08" length="short" rot="R180"/>
<pin name="P3" x="10.16" y="2.54" length="short" rot="R180"/>
<pin name="P4" x="10.16" y="0" length="short" rot="R180"/>
<pin name="P5" x="10.16" y="-2.54" length="short" rot="R180"/>
<pin name="P6" x="10.16" y="-5.08" length="short" rot="R180"/>
<pin name="P7" x="10.16" y="-7.62" length="short" rot="R180"/>
</symbol>
<symbol name="PWRN">
<text x="-0.635" y="-0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="1.905" y="-5.842" size="1.27" layer="95" rot="R90">GND</text>
<text x="1.905" y="2.54" size="1.27" layer="95" rot="R90">VCC</text>
<pin name="GND" x="0" y="-7.62" visible="pad" length="middle" direction="pwr" rot="R90"/>
<pin name="VCC" x="0" y="7.62" visible="pad" length="middle" direction="pwr" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PCF8574">
<description>Remote 8-Bit I/O Expander for I²C Bus</description>
<gates>
<gate name="IC$1" symbol="PCF8574" x="0" y="0"/>
<gate name="PWR" symbol="PWRN" x="0" y="27.94"/>
</gates>
<devices>
<device name="P" package="DIL16">
<connects>
<connect gate="IC$1" pin="/INT" pad="13"/>
<connect gate="IC$1" pin="A0" pad="1"/>
<connect gate="IC$1" pin="A1" pad="2"/>
<connect gate="IC$1" pin="A2" pad="3"/>
<connect gate="IC$1" pin="P0" pad="4"/>
<connect gate="IC$1" pin="P1" pad="5"/>
<connect gate="IC$1" pin="P2" pad="6"/>
<connect gate="IC$1" pin="P3" pad="7"/>
<connect gate="IC$1" pin="P4" pad="9"/>
<connect gate="IC$1" pin="P5" pad="10"/>
<connect gate="IC$1" pin="P6" pad="11"/>
<connect gate="IC$1" pin="P7" pad="12"/>
<connect gate="IC$1" pin="SCL" pad="14"/>
<connect gate="IC$1" pin="SDA" pad="15"/>
<connect gate="PWR" pin="GND" pad="8"/>
<connect gate="PWR" pin="VCC" pad="16"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="AP" package="DIL16">
<connects>
<connect gate="IC$1" pin="/INT" pad="13"/>
<connect gate="IC$1" pin="A0" pad="1"/>
<connect gate="IC$1" pin="A1" pad="2"/>
<connect gate="IC$1" pin="A2" pad="3"/>
<connect gate="IC$1" pin="P0" pad="4"/>
<connect gate="IC$1" pin="P1" pad="5"/>
<connect gate="IC$1" pin="P2" pad="6"/>
<connect gate="IC$1" pin="P3" pad="7"/>
<connect gate="IC$1" pin="P4" pad="9"/>
<connect gate="IC$1" pin="P5" pad="10"/>
<connect gate="IC$1" pin="P6" pad="11"/>
<connect gate="IC$1" pin="P7" pad="12"/>
<connect gate="IC$1" pin="SCL" pad="14"/>
<connect gate="IC$1" pin="SDA" pad="15"/>
<connect gate="PWR" pin="GND" pad="8"/>
<connect gate="PWR" pin="VCC" pad="16"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="T" package="SO16">
<connects>
<connect gate="IC$1" pin="/INT" pad="13"/>
<connect gate="IC$1" pin="A0" pad="1"/>
<connect gate="IC$1" pin="A1" pad="2"/>
<connect gate="IC$1" pin="A2" pad="3"/>
<connect gate="IC$1" pin="P0" pad="4"/>
<connect gate="IC$1" pin="P1" pad="5"/>
<connect gate="IC$1" pin="P2" pad="6"/>
<connect gate="IC$1" pin="P3" pad="7"/>
<connect gate="IC$1" pin="P4" pad="9"/>
<connect gate="IC$1" pin="P5" pad="10"/>
<connect gate="IC$1" pin="P6" pad="11"/>
<connect gate="IC$1" pin="P7" pad="12"/>
<connect gate="IC$1" pin="SCL" pad="14"/>
<connect gate="IC$1" pin="SDA" pad="15"/>
<connect gate="PWR" pin="GND" pad="8"/>
<connect gate="PWR" pin="VCC" pad="16"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="AT" package="SO16">
<connects>
<connect gate="IC$1" pin="/INT" pad="13"/>
<connect gate="IC$1" pin="A0" pad="1"/>
<connect gate="IC$1" pin="A1" pad="2"/>
<connect gate="IC$1" pin="A2" pad="3"/>
<connect gate="IC$1" pin="P0" pad="4"/>
<connect gate="IC$1" pin="P1" pad="5"/>
<connect gate="IC$1" pin="P2" pad="6"/>
<connect gate="IC$1" pin="P3" pad="7"/>
<connect gate="IC$1" pin="P4" pad="9"/>
<connect gate="IC$1" pin="P5" pad="10"/>
<connect gate="IC$1" pin="P6" pad="11"/>
<connect gate="IC$1" pin="P7" pad="12"/>
<connect gate="IC$1" pin="SCL" pad="14"/>
<connect gate="IC$1" pin="SDA" pad="15"/>
<connect gate="PWR" pin="GND" pad="8"/>
<connect gate="PWR" pin="VCC" pad="16"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="diy-modules">
<description>&lt;b&gt;DIY Modules for Arduino, Raspberry Pi, CubieBoard etc.&lt;/b&gt;
&lt;br&gt;&lt;br&gt;
The library contains a list of symbols and footprints for popular, cheap and easy-to-use electronic modules.&lt;br&gt;
The modules are intend to work with microprocessor-based platforms such as &lt;a href="http://arduino.cc"&gt;Arduino&lt;/a&gt;, &lt;a href="http://raspberrypi.org/"&gt;Raspberry Pi&lt;/a&gt;, &lt;a href="http://cubieboard.org/"&gt;CubieBoard&lt;/a&gt;, &lt;a href="http://beagleboard.org/"&gt;BeagleBone&lt;/a&gt; and many others. There are many manufacturers of the modules in the world. Almost all of them can be bought on &lt;a href="ebay.com"&gt;ebay.com&lt;/a&gt;.&lt;br&gt;
&lt;br&gt;
By using this library, you can design a PCB for devices created with usage of modules. Even if you do not need to create PCB design, you can also use the library to quickly document your work by drawing schematics of devices built by you.&lt;br&gt;
&lt;br&gt;
The latest version, examples, photos and much more can be found at: &lt;b&gt;&lt;a href="http://diymodules.org/eagle"&gt;diymodules.org/eagle&lt;/a&gt;&lt;/b&gt;&lt;br&gt;&lt;br&gt;
Comments, suggestions and bug reports please send to: &lt;b&gt;&lt;a href="mailto:eagle@diymodules.org"&gt;eagle@diymodules.org&lt;/b&gt;&lt;/a&gt;&lt;br&gt;&lt;br&gt;
&lt;i&gt;Version: 1.8.0 (2017-Jul-02)&lt;/i&gt;&lt;br&gt;
&lt;i&gt;Created by: Miroslaw Brudnowski&lt;/i&gt;&lt;br&gt;&lt;br&gt;
&lt;i&gt;Released under the Creative Commons Attribution 4.0 International License: &lt;a href="http://creativecommons.org/licenses/by/4.0"&gt;http://creativecommons.org/licenses/by/4.0&lt;/a&gt;&lt;/i&gt;
&lt;br&gt;&lt;br&gt;
&lt;center&gt;
&lt;a href="http://diymodules.org/eagle"&gt;&lt;img src="http://www.diymodules.org/img/diymodules-lbr-image.php?v=1.8.0" alt="DIYmodules.org"&gt;&lt;/a&gt;
&lt;/center&gt;</description>
<packages>
<package name="ETHERNET-ENC28J60">
<description>&lt;b&gt;Ethernet Module&lt;/b&gt; based on &lt;b&gt;ENC28J60&lt;/b&gt; chip</description>
<wire x1="-25.4" y1="16.51" x2="25.4" y2="16.51" width="0.127" layer="21"/>
<wire x1="25.4" y1="16.51" x2="25.4" y2="-16.51" width="0.127" layer="21"/>
<wire x1="25.4" y1="-16.51" x2="-25.4" y2="-16.51" width="0.127" layer="21"/>
<wire x1="-25.4" y1="-16.51" x2="-25.4" y2="-8.001" width="0.127" layer="21"/>
<hole x="-21.844" y="13.97" drill="2"/>
<hole x="21.844" y="13.97" drill="2"/>
<hole x="-21.844" y="-13.97" drill="2"/>
<hole x="21.844" y="-13.97" drill="2"/>
<pad name="1" x="22.86" y="-6.35" drill="1" shape="square"/>
<pad name="2" x="20.32" y="-6.35" drill="1"/>
<pad name="3" x="22.86" y="-3.81" drill="1"/>
<pad name="4" x="20.32" y="-3.81" drill="1"/>
<pad name="5" x="22.86" y="-1.27" drill="1"/>
<pad name="6" x="20.32" y="-1.27" drill="1"/>
<pad name="7" x="22.86" y="1.27" drill="1"/>
<pad name="8" x="20.32" y="1.27" drill="1"/>
<pad name="9" x="22.86" y="3.81" drill="1"/>
<pad name="10" x="20.32" y="3.81" drill="1"/>
<pad name="11" x="22.86" y="6.35" drill="1"/>
<pad name="12" x="20.32" y="6.35" drill="1"/>
<wire x1="-25.4" y1="-8.001" x2="-25.4" y2="8.001" width="0.127" layer="21"/>
<wire x1="-25.4" y1="8.001" x2="-25.4" y2="16.51" width="0.127" layer="21"/>
<wire x1="24.13" y1="-6.985" x2="23.495" y2="-7.62" width="0.127" layer="21"/>
<wire x1="23.495" y1="-7.62" x2="22.225" y2="-7.62" width="0.127" layer="21"/>
<wire x1="22.225" y1="-7.62" x2="21.59" y2="-6.985" width="0.127" layer="21"/>
<wire x1="21.59" y1="-6.985" x2="20.955" y2="-7.62" width="0.127" layer="21"/>
<wire x1="20.955" y1="-7.62" x2="19.685" y2="-7.62" width="0.127" layer="21"/>
<wire x1="19.685" y1="-7.62" x2="19.05" y2="-6.985" width="0.127" layer="21"/>
<wire x1="19.05" y1="-6.985" x2="19.05" y2="-5.715" width="0.127" layer="21"/>
<wire x1="19.05" y1="-5.715" x2="19.685" y2="-5.08" width="0.127" layer="21"/>
<wire x1="19.685" y1="-5.08" x2="19.05" y2="-4.445" width="0.127" layer="21"/>
<wire x1="19.05" y1="-4.445" x2="19.05" y2="-3.175" width="0.127" layer="21"/>
<wire x1="19.05" y1="-3.175" x2="19.685" y2="-2.54" width="0.127" layer="21"/>
<wire x1="19.685" y1="-2.54" x2="19.05" y2="-1.905" width="0.127" layer="21"/>
<wire x1="19.05" y1="-1.905" x2="19.05" y2="-0.635" width="0.127" layer="21"/>
<wire x1="19.05" y1="-0.635" x2="19.685" y2="0" width="0.127" layer="21"/>
<wire x1="19.685" y1="0" x2="19.05" y2="0.635" width="0.127" layer="21"/>
<wire x1="19.05" y1="0.635" x2="19.05" y2="1.905" width="0.127" layer="21"/>
<wire x1="19.05" y1="1.905" x2="19.685" y2="2.54" width="0.127" layer="21"/>
<wire x1="19.685" y1="2.54" x2="19.05" y2="3.175" width="0.127" layer="21"/>
<wire x1="19.05" y1="3.175" x2="19.05" y2="4.445" width="0.127" layer="21"/>
<wire x1="19.05" y1="4.445" x2="19.685" y2="5.08" width="0.127" layer="21"/>
<wire x1="19.685" y1="5.08" x2="19.05" y2="5.715" width="0.127" layer="21"/>
<wire x1="19.05" y1="5.715" x2="19.05" y2="6.985" width="0.127" layer="21"/>
<wire x1="19.05" y1="6.985" x2="19.685" y2="7.62" width="0.127" layer="21"/>
<wire x1="19.685" y1="7.62" x2="20.955" y2="7.62" width="0.127" layer="21"/>
<wire x1="20.955" y1="7.62" x2="21.59" y2="6.985" width="0.127" layer="21"/>
<wire x1="21.59" y1="6.985" x2="22.225" y2="7.62" width="0.127" layer="21"/>
<wire x1="22.225" y1="7.62" x2="23.495" y2="7.62" width="0.127" layer="21"/>
<wire x1="23.495" y1="7.62" x2="24.13" y2="6.985" width="0.127" layer="21"/>
<wire x1="24.13" y1="6.985" x2="24.13" y2="5.715" width="0.127" layer="21"/>
<wire x1="24.13" y1="5.715" x2="23.495" y2="5.08" width="0.127" layer="21"/>
<wire x1="23.495" y1="5.08" x2="24.13" y2="4.445" width="0.127" layer="21"/>
<wire x1="24.13" y1="4.445" x2="24.13" y2="3.175" width="0.127" layer="21"/>
<wire x1="24.13" y1="3.175" x2="23.495" y2="2.54" width="0.127" layer="21"/>
<wire x1="23.495" y1="2.54" x2="24.13" y2="1.905" width="0.127" layer="21"/>
<wire x1="24.13" y1="1.905" x2="24.13" y2="0.635" width="0.127" layer="21"/>
<wire x1="24.13" y1="0.635" x2="23.495" y2="0" width="0.127" layer="21"/>
<wire x1="23.495" y1="0" x2="24.13" y2="-0.635" width="0.127" layer="21"/>
<wire x1="24.13" y1="-0.635" x2="24.13" y2="-1.905" width="0.127" layer="21"/>
<wire x1="24.13" y1="-1.905" x2="23.495" y2="-2.54" width="0.127" layer="21"/>
<wire x1="23.495" y1="-2.54" x2="24.13" y2="-3.175" width="0.127" layer="21"/>
<wire x1="24.13" y1="-3.175" x2="24.13" y2="-4.445" width="0.127" layer="21"/>
<wire x1="24.13" y1="-4.445" x2="23.495" y2="-5.08" width="0.127" layer="21"/>
<wire x1="23.495" y1="-5.08" x2="24.13" y2="-5.715" width="0.127" layer="21"/>
<wire x1="24.13" y1="-5.715" x2="24.13" y2="-6.985" width="0.127" layer="21"/>
<wire x1="-25.4" y1="8.001" x2="-4.318" y2="8.001" width="0.127" layer="21"/>
<wire x1="-4.318" y1="8.001" x2="-4.318" y2="-8.001" width="0.127" layer="21"/>
<wire x1="-4.318" y1="-8.001" x2="-25.4" y2="-8.001" width="0.127" layer="21"/>
<text x="-14.605" y="0" size="1.778" layer="21" align="center">RJ45</text>
<text x="0" y="17.78" size="1.27" layer="25" align="bottom-center">&gt;NAME</text>
<text x="0" y="-17.78" size="1.27" layer="27" align="top-center">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="ETHERNET-ENC28J60">
<description>&lt;b&gt;Ethernet Module&lt;/b&gt; based on &lt;b&gt;ENC28J60&lt;/b&gt; chip</description>
<pin name="GND.1" x="25.4" y="-12.7" length="middle" direction="pwr" rot="R180"/>
<pin name="3V3" x="25.4" y="-10.16" length="middle" direction="pwr" rot="R180"/>
<pin name="CS" x="25.4" y="-7.62" length="middle" rot="R180"/>
<pin name="RST" x="25.4" y="-5.08" length="middle" rot="R180"/>
<pin name="SI" x="25.4" y="-2.54" length="middle" rot="R180"/>
<pin name="SCK" x="25.4" y="0" length="middle" rot="R180"/>
<pin name="WOL" x="25.4" y="2.54" length="middle" rot="R180"/>
<pin name="SO" x="25.4" y="5.08" length="middle" rot="R180"/>
<pin name="CLK" x="25.4" y="7.62" length="middle" rot="R180"/>
<pin name="INT" x="25.4" y="10.16" length="middle" rot="R180"/>
<pin name="GND.2" x="25.4" y="12.7" length="middle" direction="pwr" rot="R180"/>
<pin name="5V" x="25.4" y="15.24" length="middle" direction="pwr" rot="R180"/>
<wire x1="20.32" y1="17.78" x2="20.32" y2="-15.24" width="0.254" layer="94"/>
<wire x1="20.32" y1="-15.24" x2="-25.4" y2="-15.24" width="0.254" layer="94"/>
<wire x1="-25.4" y1="-15.24" x2="-25.4" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-25.4" y1="-7.62" x2="-25.4" y2="10.16" width="0.254" layer="94"/>
<wire x1="-25.4" y1="10.16" x2="-25.4" y2="17.78" width="0.254" layer="94"/>
<wire x1="-25.4" y1="17.78" x2="20.32" y2="17.78" width="0.254" layer="94"/>
<wire x1="-25.4" y1="-7.62" x2="-2.54" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-7.62" x2="-2.54" y2="10.16" width="0.254" layer="94"/>
<wire x1="-2.54" y1="10.16" x2="-25.4" y2="10.16" width="0.254" layer="94"/>
<text x="-13.97" y="1.27" size="2.54" layer="94" align="center">RJ-45</text>
<text x="-22.86" y="22.86" size="1.778" layer="95">&gt;NAME</text>
<text x="-22.86" y="20.32" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="ETHERNET-ENC28J60" prefix="M">
<description>&lt;b&gt;Ethernet Module&lt;/b&gt; based on &lt;b&gt;ENC28J60&lt;/b&gt; chip
&lt;p&gt;&lt;b&gt;&lt;a href="http://www.ebay.com/sch/end28j60+ethernet+lan+module"&gt;Click here to find device on ebay.com&lt;/a&gt;&lt;/b&gt;&lt;br /&gt;
&lt;b&gt;Note:&lt;/b&gt; There are many variants. Search for the proper version.&lt;/p&gt;

&lt;p&gt;&lt;img alt="photo" src="http://www.diymodules.org/img/device-photo.php?name=ETHERNET-ENC28J60"&gt;&lt;/p&gt;</description>
<gates>
<gate name="G$1" symbol="ETHERNET-ENC28J60" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ETHERNET-ENC28J60">
<connects>
<connect gate="G$1" pin="3V3" pad="2"/>
<connect gate="G$1" pin="5V" pad="12"/>
<connect gate="G$1" pin="CLK" pad="9"/>
<connect gate="G$1" pin="CS" pad="3"/>
<connect gate="G$1" pin="GND.1" pad="1"/>
<connect gate="G$1" pin="GND.2" pad="11"/>
<connect gate="G$1" pin="INT" pad="10"/>
<connect gate="G$1" pin="RST" pad="4"/>
<connect gate="G$1" pin="SCK" pad="6"/>
<connect gate="G$1" pin="SI" pad="5"/>
<connect gate="G$1" pin="SO" pad="8"/>
<connect gate="G$1" pin="WOL" pad="7"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1" urn="urn:adsk.eagle:library:371">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
 GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
 Please keep in mind, that these devices are necessary for the
 automatic wiring of the supply signals.&lt;p&gt;
 The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
 In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
 &lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND" urn="urn:adsk.eagle:symbol:26925/1" library_version="1">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" urn="urn:adsk.eagle:component:26954/1" prefix="GND" library_version="1">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="teensypp" deviceset="ARDUINO-TEENSY++" device=""/>
<part name="U$2" library="i2c" deviceset="PCF8574" device="T"/>
<part name="M1" library="diy-modules" deviceset="ETHERNET-ENC28J60" device=""/>
<part name="GND1" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND2" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
<part name="GND3" library="supply1" library_urn="urn:adsk.eagle:library:371" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="60.96" y="58.42" smashed="yes">
<attribute name="NAME" x="40.64" y="91.44" size="1.778" layer="95"/>
<attribute name="VALUE" x="58.42" y="43.18" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="U$2" gate="IC$1" x="144.78" y="73.66" smashed="yes">
<attribute name="NAME" x="139.7" y="88.9" size="1.778" layer="95"/>
<attribute name="VALUE" x="139.7" y="60.96" size="1.778" layer="96"/>
</instance>
<instance part="U$2" gate="PWR" x="167.64" y="60.96" smashed="yes">
<attribute name="NAME" x="169.545" y="60.325" size="1.778" layer="95"/>
</instance>
<instance part="M1" gate="G$1" x="137.16" y="40.64" smashed="yes" rot="R180">
<attribute name="NAME" x="160.02" y="17.78" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="160.02" y="20.32" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="GND1" gate="1" x="30.48" y="86.36" smashed="yes" rot="R270">
<attribute name="VALUE" x="27.94" y="88.9" size="1.778" layer="96" rot="R270"/>
</instance>
<instance part="GND2" gate="1" x="167.64" y="50.8" smashed="yes">
<attribute name="VALUE" x="165.1" y="48.26" size="1.778" layer="96"/>
</instance>
<instance part="GND3" gate="1" x="109.22" y="53.34" smashed="yes" rot="R270">
<attribute name="VALUE" x="106.68" y="55.88" size="1.778" layer="96" rot="R270"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="SCL" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="0,PWM,INT0"/>
<wire x1="33.02" y1="81.28" x2="27.94" y2="81.28" width="0.1524" layer="91"/>
<label x="27.94" y="81.28" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U$2" gate="IC$1" pin="SCL"/>
<wire x1="134.62" y1="68.58" x2="124.46" y2="68.58" width="0.1524" layer="91"/>
<label x="124.46" y="68.58" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="SDA" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="1,PWM,INT1"/>
<wire x1="33.02" y1="78.74" x2="27.94" y2="78.74" width="0.1524" layer="91"/>
<label x="27.94" y="78.74" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="U$2" gate="IC$1" pin="SDA"/>
<wire x1="134.62" y1="66.04" x2="124.46" y2="66.04" width="0.1524" layer="91"/>
<label x="124.46" y="66.04" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GND"/>
<pinref part="GND1" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="U$2" gate="PWR" pin="GND"/>
<pinref part="GND2" gate="1" pin="GND"/>
</segment>
<segment>
<pinref part="M1" gate="G$1" pin="GND.1"/>
<pinref part="GND3" gate="1" pin="GND"/>
</segment>
</net>
<net name="RX" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="2,RX,INT2"/>
<wire x1="33.02" y1="76.2" x2="17.78" y2="76.2" width="0.1524" layer="91"/>
<label x="17.78" y="76.2" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="TX" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="3,TX,INT3"/>
<wire x1="33.02" y1="73.66" x2="17.78" y2="73.66" width="0.1524" layer="91"/>
<label x="17.78" y="73.66" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="E0" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="8"/>
<wire x1="33.02" y1="60.96" x2="25.4" y2="60.96" width="0.1524" layer="91"/>
<label x="25.4" y="60.96" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="E1" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="9"/>
<wire x1="33.02" y1="58.42" x2="25.4" y2="58.42" width="0.1524" layer="91"/>
<label x="25.4" y="58.42" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="T1" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="10"/>
<wire x1="33.02" y1="55.88" x2="10.16" y2="55.88" width="0.1524" layer="91"/>
<label x="10.16" y="55.88" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="T2" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="11"/>
<wire x1="33.02" y1="53.34" x2="10.16" y2="53.34" width="0.1524" layer="91"/>
<label x="10.16" y="53.34" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="T3" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="12"/>
<wire x1="33.02" y1="50.8" x2="10.16" y2="50.8" width="0.1524" layer="91"/>
<label x="10.16" y="50.8" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="T4" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="13"/>
<wire x1="33.02" y1="48.26" x2="10.16" y2="48.26" width="0.1524" layer="91"/>
<label x="10.16" y="48.26" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="T5" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="14,PWM"/>
<wire x1="33.02" y1="45.72" x2="10.16" y2="45.72" width="0.1524" layer="91"/>
<label x="10.16" y="45.72" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="T6" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="15,PWM"/>
<wire x1="33.02" y1="43.18" x2="10.16" y2="43.18" width="0.1524" layer="91"/>
<label x="10.16" y="43.18" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="T7" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="16,PWM"/>
<wire x1="33.02" y1="40.64" x2="10.16" y2="40.64" width="0.1524" layer="91"/>
<label x="10.16" y="40.64" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="T8" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="17"/>
<wire x1="33.02" y1="38.1" x2="10.16" y2="38.1" width="0.1524" layer="91"/>
<label x="10.16" y="38.1" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="SS" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="20"/>
<wire x1="83.82" y1="68.58" x2="91.44" y2="68.58" width="0.1524" layer="91"/>
<label x="91.44" y="68.58" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="SCLK" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="21"/>
<wire x1="83.82" y1="71.12" x2="91.44" y2="71.12" width="0.1524" layer="91"/>
<label x="91.44" y="71.12" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="MOSI" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="22"/>
<wire x1="83.82" y1="73.66" x2="91.44" y2="73.66" width="0.1524" layer="91"/>
<label x="91.44" y="73.66" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="MISO" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="23"/>
<wire x1="83.82" y1="76.2" x2="91.44" y2="76.2" width="0.1524" layer="91"/>
<label x="91.44" y="76.2" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="M1" gate="G$1" pin="3V3"/>
<wire x1="111.76" y1="50.8" x2="101.6" y2="50.8" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="M1" gate="G$1" pin="CS"/>
<wire x1="111.76" y1="48.26" x2="101.6" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="M1" gate="G$1" pin="RST"/>
<wire x1="111.76" y1="45.72" x2="101.6" y2="45.72" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="M1" gate="G$1" pin="SI"/>
<wire x1="111.76" y1="43.18" x2="101.6" y2="43.18" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="M1" gate="G$1" pin="SCK"/>
<wire x1="111.76" y1="40.64" x2="101.6" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="M1" gate="G$1" pin="SO"/>
<wire x1="111.76" y1="35.56" x2="101.6" y2="35.56" width="0.1524" layer="91"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
