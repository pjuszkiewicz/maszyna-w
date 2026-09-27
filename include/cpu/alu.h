#pragma once

#include <cstdint>

class ALU
{
public:
    ALU() = default;

    // Internal functions
    uint8_t GetValue() { return m_value; }
    void SetValue(uint8_t value) { m_value = value; }

    void Add(uint8_t value) { m_value += value; }
    void Subtract(uint8_t value) { m_value -= value; }

    // External functions
    bool IsWeak() { return m_weak; }
    void SetWeak(bool value) { m_weak = value; }

    bool IsDod() { return m_dod; }
    void SetDod(bool value) { m_dod = value; }

    bool IsOde() { return m_ode; }
    void SetOde(bool value) { m_ode = value; }

    bool IsPrzep() { return m_przep; }
    void SetPrzep(bool value) { m_przep = value; }

    bool IsWeja() { return m_weja; }
    void SetWeja(bool value) { m_weja = value; }

    bool IsWyak() { return m_wyak; }
    void SetWyak(bool value) { m_wyak = value; }

private:
    uint8_t m_value = 0;

    bool m_weak = false;
    bool m_dod = false;
    bool m_ode = false;
    bool m_przep = false;
    bool m_weja = false;
    bool m_wyak = false;
};