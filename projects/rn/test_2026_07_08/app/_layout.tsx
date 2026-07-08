import React from 'react';
import { Stack } from 'expo-router';
import { StatusBar } from 'expo-status-bar';

export default function RootLayout() {
  return (
    <>
      <StatusBar style="dark" />
      <Stack>
        <Stack.Screen name="index" options={{ title: '记账', headerTitleAlign: 'center' }} />
        <Stack.Screen name="records" options={{ title: '账单', headerTitleAlign: 'center' }} />
        <Stack.Screen name="stats" options={{ title: '统计', headerTitleAlign: 'center' }} />
        <Stack.Screen
          name="add"
          options={{
            presentation: 'modal',
            title: '记一笔',
            headerTitleAlign: 'center',
          }}
        />
      </Stack>
    </>
  );
}
