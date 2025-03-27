<?php

namespace App\Http\Controllers\Api;
use Illuminate\Http\Request;

use App\Models\TransaksiSensor;
use App\Http\Controllers\Controller;

//import resource PostResource
use App\Http\Resources\TransaksiSensorResource;

class TransaksiSensorController extends Controller
{
     /**
     * index
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        // Get all transactions from TransaksiSensor model, paginated
        $transaksiSensor = TransaksiSensor::latest()->paginate(5);

        // Return a collection of transactions as a resource
        return TransaksiSensorResource::collection($transaksiSensor);
    }

        /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        $validatedData = $request->validate([
            'nama_sensor' => 'required|string|max:255',
            'nilai1' => 'required|integer',
            'nilai2' => 'required|integer',
        ]);

        $transaksiSensor = TransaksiSensor::create($validatedData);

        return new TransaksiSensorResource($transaksiSensor);
    }

        /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        $transaksiSensor = TransaksiSensor::findOrFail($id);

        return new TransaksiSensorResource($transaksiSensor);
    }

        /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, $id)
    {
        $validatedData = $request->validate([
            'nama_sensor' => 'required|string|max:255',
            'nilai1' => 'required|integer',
            'nilai2' => 'required|integer',
        ]);

        $transaksiSensor = TransaksiSensor::findOrFail($id);
        $transaksiSensor->update($validatedData);

        return new TransaksiSensorResource($transaksiSensor);
    }

        /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        $transaksiSensor = TransaksiSensor::findOrFail($id);
        $transaksiSensor->delete();

        return response()->json(['message' => 'Deleted Succesfully'],204);
    }


}