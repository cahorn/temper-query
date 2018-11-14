/*
 * Copyright © 2018 C. Ansel Horn <ansel@horn.name>
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See the
 * COPYING file for more details.
 */

#include <stdio.h>

#include <hidapi/hidapi.h>

#define VENDOR_ID  0x413d
#define PRODUCT_ID 0x2107

// Opening the device by VID/PID fails to open the *correct interface* of the
// HID device described by the VID/PIN pair. Instead, a workaround that opens
// the correct interface by its path is used.
//#define OPEN_BY_VID_PID

#define QUERY     {0x01, 0x80, 0x33, 0x01, 0x00, 0x00, 0x00, 0x00}
#define QUERY_LEN 8
#define DATA_LEN  8

/*
 * Initializes the TEMPer device using its vendor and product ID.
 */
hid_device* init_device()
{
    // Attempt to open and return TEMPer device
    hid_device *dev;
#ifdef OPEN_BY_VID_PID
    dev = hid_open( VENDOR_ID, PRODUCT_ID, NULL );
#else
    struct hid_device_info *infos = hid_enumerate( VENDOR_ID, PRODUCT_ID );
    if ( infos )
    {
        struct hid_device_info *info;
        for ( info = infos; info; info = info->next )
        {
            if ( info->interface_number == 1 )
            {
                dev = hid_open_path( info->path );
            }
        }
        hid_free_enumeration( infos );
    }
#endif
    if ( !dev )
    {
        fprintf( stderr, "Error: could not access TEMPer device\n" );
        fwprintf( stderr, hid_error( dev ) );
    }
    return dev;
}


/*
 * Queries the TEMPer device for the current temperature, in degrees Celsius,
 * and returns it.
 */
float query_temp(hid_device* dev)
{
    // Send the temperature query to the device
    unsigned char query[QUERY_LEN] = QUERY;
    if ( hid_write( dev, query, QUERY_LEN ) < QUERY_LEN )
    {
        fprintf( stderr, "Error: could not write to TEMPer device\n" );
        return 0.0;
    }
    // Receive the raw temperature data response
    unsigned char data[DATA_LEN];
    if ( hid_read_timeout( dev, data, DATA_LEN, 1000 ) < DATA_LEN )
    {
        fprintf( stderr, "Error: could not read from TEMPer device\n" );
        return 0.0;
    }
    // Parse the raw response into a single temperature value
    float temp = (float) (data[2] << 8 | data[3]) / 100.0;
    return temp;
}


int main(int argc, char** argv)
{
    // Initialize HIDAPI library
    if ( hid_init() != 0 )
    {
        fprintf( stderr, "Error: could not initialize HIDAPI\n" );
        return 1;
    }
    // Initialize the TEMPer device
    hid_device *dev = init_device();
    if ( !dev )
    {
        return 2;
    }
    // Query the TEMPer device for the current temperature and print the result
    float temp = query_temp( dev );
    printf( "%.2f\n", temp );
    return 0;
}

