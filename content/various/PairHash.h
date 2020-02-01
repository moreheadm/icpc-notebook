/**
 * Author: NUS
 * Date: 2020-01-28
 * License: CC0
 * Source: NUS noteboomer
 * Description: Demonstrates hashing for pairs for use in unordered map / set
 */
#pragma once


template < typename T1 , typename T2 >
struct pair_hash {
size_t operator () ( const pair < T1 , T2 > & p ) const {
return hash < T1 >() ( p . first ) ^ hash < T2 >() ( p . second ) ;
}
};
unordered_map < pair < int , int > , int , pair_hash < int , int > > M
