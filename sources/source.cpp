// Copyright 2021 Your Name <your_email>

#include <stdexcept>
#include <algorithm>
#include <random>
#include <vector>
#include <cstdlib>
#include <iostream>

#include <header.hpp>

/* cache_sizes['1'] = 256 KB
 * cache_sizes['2'] = 1024 KB
 * cache_sizes['3'] = 6144 KB
 * 128 KB < 256 KB < 1024 KB < 6114 KB < 9171 KB
 */

ns forwardPass(size_t arrSize)
{
  int* array = new int[arrSize];
  [[maybe_unused]] int temp = 0;

  for (size_t i = 0; i < arrSize; i += LINE_SIZE)
  {
    array[i] = std::rand();
  }

  for (size_t i = 0; i < arrSize; i += LINE_SIZE)
  {
    temp = array[i];
  }

  auto startTime = Time::now();

  for (size_t i = 0; i < 1000; i++)
  {
    for (size_t j = 0; j < arrSize; j += LINE_SIZE)
    {
      temp = array[j];
    }
  }

  delete(array);
  auto stopTime = Time::now();
  std::chrono::duration<float> duration = stopTime - startTime;
  return std::chrono::duration_cast<ns>(duration / 1000);
}

ns backwardPass(size_t arrSize)
{
  int* array = new int[arrSize];
  [[maybe_unused]] int temp = 0;

  for (size_t i = 0; i < arrSize; i += LINE_SIZE)
  {
    array[i] = std::rand();
  }

  for (size_t i = 0; i < arrSize; i += LINE_SIZE)
  {
    temp = array[i];
  }

  auto startTime = Time::now();

  for (size_t i = 0; i < 1000; i++)
  {
    for (size_t j = 0; j < arrSize; j += LINE_SIZE)
    {
      temp = array[arrSize - j];
    }
  }

  delete(array);
  auto stopTime = Time::now();
  std::chrono::duration<float> duration = stopTime - startTime;
  return std::chrono::duration_cast<ns>(duration / 1000);
}

ns randomPass(size_t arrSize)
{
  int* array = new int[arrSize];
  [[maybe_unused]] int temp = 0;
  std::vector<int> idx(arrSize);

  for (size_t i = 0; i < arrSize; i += LINE_SIZE)
  {
    idx[i] = i;
    array[i] = std::rand();
  }

  for (size_t i = 0; i < arrSize; i += LINE_SIZE)
  {
    temp = array[i];
  }

  auto rng = std::default_random_engine {};
  std::shuffle(std::begin(idx), std::end(idx), rng);

  auto startTime = Time::now();

  for (size_t i = 0; i < 1000; i++)
  {
    for (size_t j = 0; j < arrSize; j += LINE_SIZE)
    {
      temp = array[idx[j]];
    }
  }

  delete(array);
  auto stopTime = Time::now();
  std::chrono::duration<float> duration = stopTime - startTime;
  return std::chrono::duration_cast<ns>(duration / 1000);
}

void investigateCache()
{
  std::vector<int> cache_sizes {MIN_CACHE_SIZE,
                                L1_CACHE_SIZE,
                                L2_CACHE_SIZE,
                                L3_CACHE_SIZE,
                                MAX_CACHE_SIZE};

  std::cout
    << "investigation:\n"
    << "\ttravel_variant: \"forward\"\n"
    << "\texperiments:"
    << std::endl;

  for (int i = 0; i < EXP_NUM; i++)
  {
    auto timeEllapsed = forwardPass(cache_sizes[i]);
    std::cout
      << "\t- experiment:\n"
      << "\t\tnumber: " << i + 1 << std::endl
      << "\t\tinput_data:\n"
      << "\t\t\tbuffer_size: " << cache_sizes[i]*4/1024 << "KB" << std::endl
      << "\t\tresults:\n"
      << "\t\t\tduraion: " << timeEllapsed.count() << " ns\n"
      << std::endl;
  }

  std::cout
    << "investigation:\n"
    << "\ttravel_variant: \"backward\"\n"
    << "\texperiments:"
    << std::endl;

  for (int i = 0; i < EXP_NUM; i++)
  {
    auto timeEllapsed = backwardPass(cache_sizes[i]);
    std::cout
      << "\t- experiment:\n"
      << "\t\tnumber: " << i + 1<< std::endl
      << "\t\tinput_data:\n"
      << "\t\t\tbuffer_size: " << cache_sizes[i]*4/1024 << "KB" << std::endl
      << "\t\tresults:\n"
      << "\t\t\tduraion: " << timeEllapsed.count() << " ns\n"
      << std::endl;
  }

  std::cout
    << "investigation:\n"
    << "\ttravel_variant: \"random\"\n"
    << "\texperiments:"
    << std::endl;

  for (int i = 0; i < EXP_NUM; i++)
  {
    auto timeEllapsed = randomPass(cache_sizes[i]);
    std::cout
      << "\t- experiment:\n"
      << "\t\tnumber: " << i + 1<< std::endl
      << "\t\tinput_data:\n"
      << "\t\t\tbuffer_size: " << cache_sizes[i]*4/1024 << "KB" << std::endl
      << "\t\tresults:\n"
      << "\t\t\tduraion: " << timeEllapsed.count() << " ns"
      << std::endl;
  }
}

