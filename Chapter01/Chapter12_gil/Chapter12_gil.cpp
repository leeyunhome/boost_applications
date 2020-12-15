// Chapter12_gil.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <boost/gil.hpp>
#include <boost/gil/packed_pixel.hpp>
#include <boost/gil/planar_pixel_iterator.hpp>
#include <boost/gil/planar_pixel_reference.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/io/png.hpp>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
	typedef boost::mpl::vector<
		boost::gil::gray8_image_t,
		boost::gil::gray16_image_t,
		boost::gil::rgb8_image_t
	> img_types;

	std::string file_name(argv[1]);
	boost::gil::rgb8_planar_image_t<img_types> source;

}
