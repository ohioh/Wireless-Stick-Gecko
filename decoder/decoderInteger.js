// The Thing Network Decoder
// uplink payload formatter
///////////////////////////////////////////////////////////////////////////////////////////
// https://www.sensirion.com/en/environmental-sensors/particulate-matter-sensors-pm25/
/*
string

Unsigned 16-bit integer values:
onemess 0..2    Mass Concentration PM1.0 [μg/m³]    
twomess 3..5    Mass Concentration PM2.5 [μg/m³]
fourmes 6..8    Mass Concentration PM4.0 [μg/m³]
fivemes 9..11   Mass Concentration PM10 [μg/m³]
tenmess 12..14  Number Concentration PM0.5  [#/cm³]
onenumb 15..17  Number Concentration PM1.0  [#/cm³]
twonumb 18..20  Number Concentration PM2.5  [#/cm³]
fournum 21..23  Number Concentration PM4.0  [#/cm³]
fivenum 24..26  Number Concentration PM10 [#/cm³]
tennumb 27..29  Typical Particle Size8[nm]
avrmess         
vocmess
tempmes
humimes
presmes
c02mess

TODO: Calculate missing values

Unsigned 16-bit integer values9Byte #DatatypeDescriptionSHDLCI2C0..10..2big-endian unsigned 16-bit integerMass Concentration PM1.0 [μg/m³]2..33..5Mass Concentration PM2.5 [μg/m³]4..56..8Mass Concentration PM4.0 [μg/m³]6..79..11Mass Concentration PM10 [μg/m³]8..912..14Number Concentration PM0.5  [#/cm³]10..1115..17Number Concentration PM1.0  [#/cm³]12..1318..20Number Concentration PM2.5  [#/cm³]14..1521..23Number Concentration PM4.0  [#/cm³]16..1724..26Number Concentration PM10 [#/cm³]18..1927..29Typical Particle Size8[nm]
*/
///////////////////////////////////////////////////////////////////////////////////////////
function DecoderInteger1(bytes, port) 
{
    var decoder_var4 = bytes[0];

    return {
        var: decoder_var
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
function DecoderInteger2(bytes, port) 
{
    var decoder_var8 = bytes[0] << 8 | bytes[1];

    return {
        var: decoder_var8
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
function DecoderInteger4(bytes, port) 
{
    var decoder_var16 = bytes[0] << 24 | bytes[1] << 16 | bytes[2] << 8 | bytes[3];

    return {
        var: decoder_var16
    }
}
///////////////////////////////////////////////////////////////////////////////////////////